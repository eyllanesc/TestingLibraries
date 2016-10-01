#include "botanwrapper.h"
#include <QByteArray>
#include <QDebug>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <memory>

#include <botan/botan.h>
#include <botan/pipe.h>
#include <botan/filters.h>
#include <botan/pbkdf2.h>
#include <botan/hmac.h>
#include <botan/sha160.h>
#include <botan/kdf.h>

using namespace std;
using namespace Botan;

BotanWrapper::BotanWrapper(QObject *parent) : QObject(parent)
{
    // set the default salt size
	mSalt.resize(48);

    // set the default salt
    const unsigned saltSize = mSalt.size();
    for (unsigned i = 0; i < saltSize; i++) {
		mSalt[i] = i;
	}

    // set the default password
    mPassword = hash("!@&^jdshUG24!T^!@*&!Y@()&^909+!-@!@#07");
}

QString BotanWrapper::hash(QString data)
{
	try {
		Pipe pipe(new Hash_Filter("SHA-1"));
        pipe.process_msg(data.toStdString());
		QString Value = QString::fromStdString(pipe.read_all_as_string(0));
		return Value;
	} catch (...) {
		return "";
	}
}

QString BotanWrapper::hexHash(QString data)
{
	try {
		Pipe pipe(new Hash_Filter("SHA-1"), new Hex_Encoder);
        pipe.process_msg(data.toStdString());
		QString Value = QString::fromStdString(pipe.read_all_as_string(0));
		return Value;
	} catch (...) {
		return "";
	}
}

QString BotanWrapper::encode(QString data)
{
	try {
		Pipe pipe(new Base64_Encoder);
        pipe.process_msg(data.toStdString());
		QString Value = QString::fromStdString(pipe.read_all_as_string(0));
		return Value;
	} catch (...) {
		return "";
	}
}

QString BotanWrapper::decode(QString data)
{
	try {
		Pipe pipe(new Base64_Decoder);
        pipe.process_msg(data.toStdString());
		QString Value = QString::fromStdString(pipe.read_all_as_string(0));
		return Value;
	} catch (...) {
		return "";
	}
}

QString BotanWrapper::encrypt(QString data)
{
	try {
        // setup the key derive functions
		PKCS5_PBKDF2 pbkdf2(new HMAC(new SHA_160));
		const u32bit PBKDF2_ITERATIONS = 8192;

        // create the KEY and IV
		KDF* kdf = get_kdf("KDF2(SHA-1)");

        // create the master key
        secure_vector < byte > mMaster = pbkdf2.derive_key(48,
				mPassword.toStdString(), &mSalt[0], mSalt.size(),
				PBKDF2_ITERATIONS).bits_of();
		SymmetricKey mKey = kdf->derive_key(32, mMaster, "salt1");
		InitializationVector mIV = kdf->derive_key(16, mMaster, "salt2");

		Pipe pipe(get_cipher("AES-256/CBC/PKCS7", mKey, mIV, ENCRYPTION),
				new Base64_Encoder);
        pipe.process_msg(data.toStdString());
		QString Value = QString::fromStdString(pipe.read_all_as_string(0));
		return Value;
	} catch (...) {
		return "";
	}
}

QString BotanWrapper::decrypt(QString data)
{
	try {
        // setup the key derive functions
		PKCS5_PBKDF2 pbkdf2(new HMAC(new SHA_160));
		const u32bit PBKDF2_ITERATIONS = 8192;

        // create the KEY and IV
		KDF* kdf = get_kdf("KDF2(SHA-1)");

        // create the master key
        secure_vector <byte> mMaster = pbkdf2.derive_key(48,
				mPassword.toStdString(), &mSalt[0], mSalt.size(),
				PBKDF2_ITERATIONS).bits_of();
		SymmetricKey mKey = kdf->derive_key(32, mMaster, "salt1");
		InitializationVector mIV = kdf->derive_key(16, mMaster, "salt2");

		Pipe pipe(new Base64_Decoder,
				get_cipher("AES-256/CBC/PKCS7", mKey, mIV, DECRYPTION));
        pipe.process_msg(data.toStdString());
		QString Value = QString::fromStdString(pipe.read_all_as_string(0));
		return Value;
	} catch (...) {
		return "";
	}
}

bool BotanWrapper::encryptFile(QString source, QString destination)
{
	try {
        // setup the key derive functions
		PKCS5_PBKDF2 pbkdf2(new HMAC(new SHA_160));
		const u32bit PBKDF2_ITERATIONS = 8192;

        // create the KEY and IV
		KDF* kdf = get_kdf("KDF2(SHA-1)");

        // create the master key
        secure_vector<byte> mMaster = pbkdf2.derive_key(48,
				mPassword.toStdString(), &mSalt[0], mSalt.size(),
				PBKDF2_ITERATIONS).bits_of();
		SymmetricKey mKey = kdf->derive_key(32, mMaster, "salt1");
		InitializationVector mIV = kdf->derive_key(16, mMaster, "salt2");

        string inFilename = source.toStdString();
        string outFilename = destination.toStdString();
		std::ifstream in(inFilename.c_str(), std::ios::binary);
		std::ofstream out(outFilename.c_str(), std::ios::binary);

		Pipe pipe(get_cipher("AES-256/CBC/PKCS7", mKey, mIV, ENCRYPTION),
				new DataSink_Stream(out));
		pipe.start_msg();
		in >> pipe;
		pipe.end_msg();

		out.flush();
		out.close();
		in.close();

		return true;
	} catch (...) {
		return false;
	}
}

bool BotanWrapper::decryptFile(QString source, QString destination)
{
	try {
        // setup the key derive functions
		PKCS5_PBKDF2 pbkdf2(new HMAC(new SHA_160));
		const u32bit PBKDF2_ITERATIONS = 8192;

        // create the KEY and IV
		KDF* kdf = get_kdf("KDF2(SHA-1)");

        // create the master key
        secure_vector<byte> mMaster = pbkdf2.derive_key(48,
				mPassword.toStdString(), &mSalt[0], mSalt.size(),
				PBKDF2_ITERATIONS).bits_of();
		SymmetricKey mKey = kdf->derive_key(32, mMaster, "salt1");
		InitializationVector mIV = kdf->derive_key(16, mMaster, "salt2");

        string inFilename = source.toStdString();
        string outFilename = destination.toStdString();
		std::ifstream in(inFilename.c_str(), std::ios::binary);
		std::ofstream out(outFilename.c_str(), std::ios::binary);

		Pipe pipe(get_cipher("AES-256/CBC/PKCS7", mKey, mIV, DECRYPTION),
				new DataSink_Stream(out));
		pipe.start_msg();
		in >> pipe;
		pipe.end_msg();

		out.flush();
		out.close();
		in.close();

		return true;
	} catch (...) {
		return false;
	}
}

void BotanWrapper::setPassword(QString password)
{
    // set the password
    mPassword = password;
}

void BotanWrapper::setSalt(QString salt)
{
    QByteArray cBytes = salt.toLatin1();
    const unsigned saltSize = mSalt.size();
    for (unsigned i = 0; i < saltSize; i++) {
		mSalt[i] = cBytes[i];
	}
}

