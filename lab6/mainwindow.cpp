#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSplitter>
#include "databasemanager.h"
#include "addwindow.h"
#include "cryptoutil.h"  // 加密头文件
#include <QDateTime>     // 用于记录时间
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QTimer>
#include <QMenu>
#include <QClipboard>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QSqlRecord>
#include <QFuture>
#include <QtConcurrent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_model = nullptr;
    initSideBar();
    // 测试数据库连接
    if (DatabaseManager::instance().openDb()) {
        ui->statusbar->showMessage("数据库连接成功！");
        initTableView();
    } else {
        ui->statusbar->showMessage("数据库连接失败，请检查日志。");
    }
    connect(&m_watcher, &QFutureWatcher<void>::finished,
            this, &MainWindow::onExportFinished);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initSideBar()
{
    // 清空现有项
    ui->listWidgetCategories->clear();

    // 添加固定分类
    QStringList categories = {
        "所有账号",
        "社交娱乐",
        "工作办公",
        "其他"
    };

    ui->listWidgetCategories->addItems(categories);

    // 默认选中第一项
    ui->listWidgetCategories->setCurrentRow(0);
}

void MainWindow::initTableView()
{
    //创建模型，使用全局数据库连接
    m_model = new QSqlTableModel(this, DatabaseManager::instance().getDb());

    //绑定表名
    m_model->setTable("accounts");

    //设置编辑策略：修改后立即更新到数据库
    m_model->setEditStrategy(QSqlTableModel::OnFieldChange);

    //执行查询，把数据拉取下来
    m_model->select();

    //设置表头别名 (让界面显示中文，而不是数据库字段名)
    m_model->setHeaderData(0, Qt::Horizontal, "ID");
    m_model->setHeaderData(1, Qt::Horizontal, "类别");
    m_model->setHeaderData(2, Qt::Horizontal, "网站/标题");
    m_model->setHeaderData(3, Qt::Horizontal, "用户名");
    m_model->setHeaderData(4, Qt::Horizontal, "密码(已加密)");
    m_model->setHeaderData(5, Qt::Horizontal, "备注");
    m_model->setHeaderData(6, Qt::Horizontal, "创建时间");

    //将模型绑定到 UI 上的视图
    ui->tableViewAccounts->setModel(m_model);

    // 细节优化：隐藏 ID 列
    // 必须在 setModel 之后调用 setColumnHidden
    ui->tableViewAccounts->setColumnHidden(0, true);

    //让列宽自动铺满
    ui->tableViewAccounts->horizontalHeader()->setStretchLastSection(true);

    ui->tableViewAccounts->setModel(m_model);
    ui->tableViewAccounts->setColumnHidden(0, true);

    // 开启右键菜单策略
    ui->tableViewAccounts->setContextMenuPolicy(Qt::CustomContextMenu);

    // 关联信号：当用户右键点击时，触发 showContextMenu 槽函数
    connect(ui->tableViewAccounts, &QTableView::customContextMenuRequested,
            this, &MainWindow::showContextMenu);
}

void MainWindow::on_actionAdd_triggered()
{
    AddWindow dlg(this);

    // 设置弹窗标题
    dlg.setWindowTitle("新增账号信息");

    // 调用 exec() 显示弹窗
    // 如果用户点了"保存" (我们在 DialogAdd 里写了 accept())，它返回 QDialog::Accepted
    // 如果用户点了"取消" 或右上角叉号，它返回 QDialog::Rejected
    int result = dlg.exec();

    //判断用户操作
    if (result == QDialog::Accepted) {
        // 用户点击了保存，这里开始写数据库插入逻辑

        saveAccountToDb(dlg);
    } else {
        // 用户点击了取消，什么都不用做
        qDebug() << "用户取消了添加";
    }
}

void MainWindow::on_listWidgetCategories_currentTextChanged(const QString &currentText)
{
    if (!m_model) return;

    if (currentText == "所有账号") {
        m_model->setFilter(""); // 清空过滤器，显示所有
    } else {
        // 相当于 SQL: WHERE category = '某类别',要给字符串加单引号
        //
        m_model->setFilter(QString("category = '%1'").arg(currentText));
    }
    m_model->select(); // 重新执行查询刷新表格
}

void MainWindow::on_searchEdit_textChanged(const QString &arg1)
{
    if (!m_model) return;

    if (arg1.isEmpty()) {
        // 如果搜索框清空了，就恢复左侧选中的分类
        QString currentCategory = ui->listWidgetCategories->currentItem()->text();
        on_listWidgetCategories_currentTextChanged(currentCategory);
        return;
    }

    // 相当于 SQL: WHERE site LIKE '%google%' OR username LIKE '%google%'
    // 这样既能搜网站名，也能搜用户名
    QString filterStr = QString("(site LIKE '%%1%') OR (username LIKE '%%1%')").arg(arg1);

    m_model->setFilter(filterStr);
    m_model->select();
}

void MainWindow::showContextMenu(const QPoint &pos)
{
    // 1. 获取鼠标点击的行索引
    QModelIndex index = ui->tableViewAccounts->indexAt(pos);
    if (!index.isValid()) return; // 如果点在空白处，不理会

    // 2. 创建菜单
    QMenu menu(this);
    QAction *actCopyUser = menu.addAction("复制用户名");
    QAction *actCopyPass = menu.addAction("复制密码");
    QAction *actDel = menu.addAction("删除此行");

    // 3. 弹出菜单并等待用户选择
    QAction *selectedItem = menu.exec(ui->tableViewAccounts->mapToGlobal(pos));

    // 获取当前行的数据
    // 第3列是用户名，第4列是加密密码 (根据你的 initTableView 里的 setHeaderData 顺序)
    // 最好检查一下列号：id=0, category=1, site=2, username=3, enc_pass=4
    int row = index.row();
    QString username = m_model->index(row, 3).data().toString();
    QString encPass  = m_model->index(row, 4).data().toString();

    // 处理点击逻辑
    if (selectedItem == actCopyUser) {
        QApplication::clipboard()->setText(username);
    }
    else if (selectedItem == actCopyPass) {
        // 解密
        QString plainPass = CryptoUtil::decrypt(encPass);
        QApplication::clipboard()->setText(plainPass);

        ui->statusbar->showMessage("密码已复制到剪贴板！(30秒后自动清除)");

        // 30秒后清空剪贴板
        QTimer::singleShot(30000, [=](){
            if (QApplication::clipboard()->text() == plainPass) {
                QApplication::clipboard()->clear();
                ui->statusbar->showMessage("剪贴板已清除");
            }
        });
    }
    else if (selectedItem == actDel) {
        on_actionDel_triggered(); // 复用删除功能
    }
}

void MainWindow::on_actionDel_triggered()
{
    // 1. 获取当前选中的行
    QModelIndexList selection = ui->tableViewAccounts->selectionModel()->selectedRows();

    if (selection.isEmpty()) {
        QMessageBox::warning(this, "提示", "请先选择要删除的账号！");
        return;
    }

    // 2. 确认提示
    int ret = QMessageBox::question(this, "确认删除", "确定要永久删除选中的账号吗？",
                                    QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::No) return;

    // 3. 执行删除
    // 因为是多选模式可能选中多行，所以用循环
    for(const QModelIndex &index : selection) {
        m_model->removeRow(index.row());
    }

    // 4. 提交更改 (如果是 OnFieldChange 策略，这一步其实 removeRow 后会自动提交，但保险起见)
    m_model->select();

    QMessageBox::information(this, "成功", "删除成功");
}

void MainWindow::saveAccountToDb(AddWindow &dlg)
{
    // 获取输入
    QString category = dlg.getCategory();
    QString site = dlg.getSite();
    QString user = dlg.getUser();
    QString rawPass = dlg.getPassword();
    QString note = dlg.getNote();

    // 加密密码 (实现 CryptoUtil)
    // 如果还没实现加密，暂时用 rawPass 代替
    QString encPass = CryptoUtil::encrypt(rawPass);

    // 执行 SQL
    QSqlQuery query;
    query.prepare("INSERT INTO accounts (category, site, username, enc_password, note, created_at) "
                  "VALUES (:cat, :site, :user, :pass, :note, :time)");

    query.bindValue(":cat", category);
    query.bindValue(":site", site);
    query.bindValue(":user", user);
    query.bindValue(":pass", encPass);
    query.bindValue(":note", note);
    query.bindValue(":time", QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm"));

    if (query.exec()) {
        QMessageBox::information(this, "成功", "账号添加成功！");

        // 刷新表格显示
        // 重新查询数据库，让新数据立即出现在界面上
        if (m_model) {
            m_model->select();
        }
    } else {
        QMessageBox::critical(this, "错误", "数据库写入失败：" + query.lastError().text());
    }
}


void MainWindow::on_actionExport_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "导出加密备份",
                                                    QDir::homePath() + "/backup.dat",
                                                    "Encrypted Data (*.dat)");
    if (fileName.isEmpty()) return;

    // [主线程] 收集数据
    // 注意：一定要在主线程把数据从 Model 里取出来，因为 QSqlTableModel 不是线程安全的，不能在后台线程里操作它
    QJsonArray jsonArray;
    int rowCount = m_model->rowCount();

    for (int i = 0; i < rowCount; ++i) {
        QSqlRecord record = m_model->record(i);
        QJsonObject jsonObj;
        jsonObj["category"] = record.value("category").toString();
        jsonObj["site"]     = record.value("site").toString();
        jsonObj["username"] = record.value("username").toString();
        jsonObj["enc_pass"] = record.value("enc_password").toString(); // 保持原有的密码加密状态
        jsonObj["note"]     = record.value("note").toString();
        jsonObj["time"]     = record.value("created_at").toString();
        jsonArray.append(jsonObj);
    }

    // 准备数据包 (转成字符串，方便传递给线程)
    QJsonDocument doc(jsonArray);
    QString rawData = doc.toJson();

    // [界面反馈] 显示“正在导出...”
    ui->statusbar->showMessage("正在后台导出并加密数据，请稍候...");
    ui->centralwidget->setEnabled(false); // 暂时禁用界面防止误操作

    // [多线程] 启动后台任务
    // 使用 Lambda 表达式捕获 fileName 和 rawData
    QFuture<void> future = QtConcurrent::run([=]() {

        // 以下代码在子线程运行

        // A. 对整个文件内容进行二次加密 (保护用户名和网站名等元数据)
        QString finalContent = CryptoUtil::encrypt(rawData);

        // B. 写入文件
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly)) {
            file.write(finalContent.toUtf8());
            file.close();
        }

        //子线程结束
    });

    // 监控任务结束
    // 当 future 结束时，m_watcher 会发出 finished 信号
    m_watcher.setFuture(future);

}

void MainWindow::onExportFinished()
{
    // 恢复界面
    ui->centralwidget->setEnabled(true);
    ui->statusbar->showMessage("导出完成！", 5000);
    QMessageBox::information(this, "系统提示", "备份文件已成功导出并加密！");
}

void MainWindow::on_actionImport_triggered()
{
    // 选择备份文件
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "选择备份文件",
                                                    QDir::homePath(),
                                                    "Encrypted Data (*.dat);;All Files (*)");
    if (fileName.isEmpty()) return;

    // 确认提示 (防止误操作)
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "确认导入",
                                  "导入操作会将备份中的数据追加到当前数据库中。\n是否继续？",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::No) return;

    // 读取并解密文件
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "错误", "无法打开文件！");
        return;
    }

    QByteArray encryptedData = file.readAll();
    file.close();

    // 全文解密 (对应导出时的 CryptoUtil::encrypt)
    QString jsonString = CryptoUtil::decrypt(QString::fromUtf8(encryptedData));

    // 解析 JSON
    QJsonParseError jsonError;
    QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8(), &jsonError);

    if (jsonError.error != QJsonParseError::NoError || !doc.isArray()) {
        QMessageBox::critical(this, "错误", "文件格式错误或解密失败！\n请确认选择了正确的文件。");
        return;
    }

    QJsonArray jsonArray = doc.array();

    // 批量写入数据库 (使用事务，速度快且安全)
    QSqlDatabase db = DatabaseManager::instance().getDb();
    db.transaction(); // 开启事务

    QSqlQuery query;
    query.prepare("INSERT INTO accounts (category, site, username, enc_password, note, created_at) "
                  "VALUES (:cat, :site, :user, :pass, :note, :time)");

    int successCount = 0;

    for (const QJsonValue &val : jsonArray) {
        QJsonObject obj = val.toObject();

        query.bindValue(":cat",  obj["category"].toString());
        query.bindValue(":site", obj["site"].toString());
        query.bindValue(":user", obj["username"].toString());

        // 注意：导出时保存的是 enc_pass (已经是加密的)，所以这里直接存入，不需要再加密一次
        query.bindValue(":pass", obj["enc_pass"].toString());

        query.bindValue(":note", obj["note"].toString());
        query.bindValue(":time", obj["time"].toString());

        if (query.exec()) {
            successCount++;
        }
    }

    // 提交事务并刷新
    if (db.commit()) {
        m_model->select(); // 刷新表格
        QMessageBox::information(this, "成功",
                                 QString("导入完成！成功恢复 %1 条数据。").arg(successCount));
    } else {
        db.rollback(); // 如果提交失败，回滚所有操作
        QMessageBox::critical(this, "失败", "数据库写入失败，已撤销操作。");
    }
}

