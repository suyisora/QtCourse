#ifndef CRYPTOUTIL_H
#define CRYPTOUTIL_H

#include <QString>
#include <QByteArray>
#include <QCryptographicHash>

class CryptoUtil
{
public:
    // 这里硬编码一个密钥，实际项目中通常由用户的主密码生成
    static const QString KEY;

    // 加密函数：明文 -> 密文 (Base64字符串)
    static QString encrypt(const QString &plainText);

    // 解密函数：密文 (Base64字符串) -> 明文
    static QString decrypt(const QString &encryptedText);
};

#endif // CRYPTOUTIL_H
