#include"SptProject.h"
using namespace spt;

#include"openssl\openssl\ssl.h"
#include"openssl\openssl\sms4.h"
#include "openssl\openssl\rand.h"

#ifdef WIN32_SIM
#define SSL_LIB_ON	(1)
extern"C" FILE * __cdecl __iob_func(unsigned i) {
	return __acrt_iob_func(i);
}
#else
#define SSL_LIB_ON	(1)
#endif // WIN32_SIM
static sms4_ede_key_t sms4_ede_e_key;
static sms4_ede_key_t sms4_ede_d_key;

int32 spt::SalGmSm4EncryData(const uint8* Data, uint8* Out, uint32 Len)
{
	uint32 l = Len / 16;
	for (uint32 i = 0; i < l; i++)
	{
		sms4_ede_encrypt(Data, Out, &sms4_ede_e_key);
		Data += 16;
		Out += 16;
	}
	return l * 16;
}

int32 spt::SalGmSm4DecryData(const uint8* Data, uint8* Out, uint32 Len)
{
	uint32 l = Len / 16;
	for (uint32 i = 0; i < l; i++)
	{
		sms4_ede_decrypt(Data, Out, &sms4_ede_d_key);
		Data += 16;
		Out += 16;
	}
	return l * 16;
}
void spt::OpenSslLibIni()
{
	static bool8 runonce = 0;
	if (!runonce)
	{
		runonce = 1;
#if SSL_LIB_ON
		SSL_library_init();
		SSL_load_error_strings();
		DbgGmSslServerIni();
		//	DbgGmSslClientIni();
#else

#endif // SSL_LIB_ON
	}
	const unsigned char user_key[48] = { 20,13,147,36,215,214,204,208,95,250,99,223,60,250,249,32,91,99,119,170,240,18,223,200,191,252,170,86,188,8,44,217,30,74,172,94,117,208,79,208,64,147,78,109,239,164,34,21 };
	sms4_ede_set_encrypt_key(&sms4_ede_e_key, user_key);
	sms4_ede_set_decrypt_key(&sms4_ede_d_key, user_key);
}
static SSL_CTX* DbgGmSslServerCtx = 0;
static SSL_CTX* DbgGmSslClientCtx = 0;
void spt::OpenSslLibClean()
{
#if SSL_LIB_ON
	if (DbgGmSslServerCtx)
	{
		SSL_CTX_free(DbgGmSslServerCtx);
	}

	DbgGmSslServerCtx = 0;
	if (DbgGmSslClientCtx)
	{
		SSL_CTX_free(DbgGmSslClientCtx);
	}
	DbgGmSslClientCtx = 0;
#endif
}

void* GmServerMothed()
{
#if SSL_LIB_ON
	if (StrCmp(DbgSimCfg::Instance().GmsslLinkMode.StrData(), "SM2-WITH-SMS4-SM3") == 0)
	{
		return(void*)GMTLS_server_method();
	}
	if (StrCmp(DbgSimCfg::Instance().GmsslLinkMode.StrData(), "ECDHE-SM2-WITH-SMS4-GCM-SM3") == 0)
	{
		return(void*)TLSv1_2_server_method();
	}
	if (StrCmp(DbgSimCfg::Instance().GmsslLinkMode.StrData(), "ECDHE-SM2-WITH-SMS4-SM3") == 0)
	{
		return(void*)TLSv1_2_server_method();
	}
#else
	return 0;
#endif
	return 0;
}

void* GmClientMothed()
{
#if SSL_LIB_ON
	if (StrCmp(DbgSimCfg::Instance().GmsslLinkMode.StrData(), "SM2-WITH-SMS4-SM3") == 0)
	{
		return(void*)GMTLS_client_method();
	}
	if (StrCmp(DbgSimCfg::Instance().GmsslLinkMode.StrData(), "ECDHE-SM2-WITH-SMS4-GCM-SM3") == 0)
	{
		return(void*)TLSv1_2_client_method();
	}
	if (StrCmp(DbgSimCfg::Instance().GmsslLinkMode.StrData(), "ECDHE-SM2-WITH-SMS4-SM3") == 0)
	{
		return(void*)TLSv1_2_client_method();
	}
#else
	return 0;
#endif
	return 0;
}


void* SslContextNew(void* GmSerMothed)
{
#if SSL_LIB_ON
	return SSL_CTX_new((const SSL_METHOD*)GmSerMothed);
#endif
	return 0;
}

#define CA_CERT_FILE (CN_GMSSL_FILE_ROOT CN_FILE_DivFlag "db_ca.pem")
#define SIGN_CERT_FILE (CN_GMSSL_FILE_ROOT CN_FILE_DivFlag "db_server_sign.crt")
#define SIGN_KEY_FILE	(CN_GMSSL_FILE_ROOT CN_FILE_DivFlag "db_server_sign.key")
#define ENC_CERT_FILE (CN_GMSSL_FILE_ROOT CN_FILE_DivFlag "db_server_enc.crt")
#define ENC_KEY_FILE (CN_GMSSL_FILE_ROOT CN_FILE_DivFlag "db_server_enc.key")
#define CLIENT_CERT_FILE (CN_GMSSL_FILE_ROOT CN_FILE_DivFlag "db_client_sign.crt")
#define CLIENT_KEY_FILE (CN_GMSSL_FILE_ROOT CN_FILE_DivFlag "db_client_sign.key")
#define CLIENT_ENC_CERT_FILE (CN_GMSSL_FILE_ROOT CN_FILE_DivFlag "db_client_enc.crt")
#define CLIENT_ENC_KEY_FILE (CN_GMSSL_FILE_ROOT CN_FILE_DivFlag "db_client_enc.key")


int32  DbgConfigGmServerSsl(void* SslContext)
{
#if SSL_LIB_ON
	SSL_CTX* ctx = (SSL_CTX*)SslContext;

	SSL_CTX_set_cipher_list(ctx, DbgSimCfg::Instance().GmsslLinkMode.StrData());
	//设置pass word
	SSL_CTX_set_default_passwd_cb_userdata(ctx, (void*)"123456");
	// 是否要求校验对方证书 若不验证客户端身份则设置为： SSL_VERIFY_NONE
	//	SSL_CTX_set_verify(ctx, SSL_VERIFY_NONE, NULL);
	//验证对方
	SSL_CTX_set_verify(ctx, DbgSimCfg::Instance().GmsslVerifyMode.Data(), NULL);
	//若验证,则放置CA证书
	int ret = SSL_CTX_load_verify_locations(ctx, CA_CERT_FILE, NULL);
	if (ret < 0)
	{
		LogErr << "SSL_CTX_load_verify_locations failed.";
	}

	//双证书模式，需要先设置签名证书，然后再设置加密证书
	//载入服务端数字签名证书
	if (SSL_CTX_use_certificate_file(ctx, SIGN_CERT_FILE, DbgSimCfg::Instance().GmsslCrtFormat.Data()) <= 0)
	{
		LogErr << "SSL_CTX_use_certificate_file SIGN_CERT_FILE err.\n";
		return(-1);
	}
	//载入服务端签名私钥
	if (SSL_CTX_use_PrivateKey_file(ctx, SIGN_KEY_FILE, DbgSimCfg::Instance().GmsslCrtFormat.Data()) <= 0)
	{
		LogErr << "SSL_CTX_use_PrivateKey_file SIGN_CERT_FILE err.\n";
		return(-1);
	}
	//检查用户私钥是否正确
	if (SSL_CTX_check_private_key(ctx) <= 0)
	{
		LogErr << "SSL_CTX_check_private_key err.\n";
		return(-1);
	}
	if (StrCmp(DbgSimCfg::Instance().GmsslLinkMode.StrData(), "SM2-WITH-SMS4-SM3") == 0)
	{
		//载入服务端加密证书
		if (SSL_CTX_use_certificate_file(ctx, ENC_CERT_FILE, DbgSimCfg::Instance().GmsslCrtFormat.Data()) <= 0)
		{
			LogErr << "SSL_CTX_use_certificate_file ENC_CERT_FILE err.\n";
			return(-1);
		}
		//载入加密私钥
		if (SSL_CTX_use_PrivateKey_file(ctx, ENC_KEY_FILE, DbgSimCfg::Instance().GmsslCrtFormat.Data()) <= 0)
		{
			LogErr << "SSL_CTX_use_PrivateKey_file ENC_KEY_FILE err.\n";
			return(-1);
		}
		//检查用户私钥是否正确
		if (!SSL_CTX_check_private_key(ctx))
		{
			LogErr << "SSL_CTX_check_private_key err.\n";
			return(-1);
		}
	}
	return 0;
#else
	return -1;
#endif
}

int32 spt::DbgGmSslServerIni()
{
	//gmssl双证书通信
	SSL_METHOD* meth = (SSL_METHOD*)GmServerMothed();

	if (!meth)
	{
		LogErr << "DbgGmSslServerIni meth is null.\n";
		return -1;
	}
	//建立新的SSL上下文 
	SSL_CTX* ctx = (SSL_CTX*)SslContextNew(meth);
	if (!ctx)
	{
		LogErr << "DbgGmSslServerIni ctx is null.\n";
		return -1;
	}
	if (DbgConfigGmServerSsl(ctx))
	{
		LogErr << "DbgGmSslServerIni DbgConfigGmServerSsl failed.\n";
		SSL_CTX_free(ctx);
		return -1;
	}
	if (DbgGmSslServerCtx)
	{
		SSL_CTX_free(DbgGmSslServerCtx);
	}
	DbgGmSslServerCtx = ctx;
	return 0;
}
bool8 spt::IsGmServerIniOk()
{
	return DbgGmSslServerCtx != 0;
}
int DbgConfigGmClientSsl(SSL_CTX* ctx)
{
	SSL_CTX_set_cipher_list(ctx, DbgSimCfg::Instance().GmsslLinkMode.StrData());

	//要求校验对方证书，表示需要验证服务器端，若不需要验证则使用  SSL_VERIFY_NONE
	//SSL_CTX_set_verify(ctx, SSL_VERIFY_NONE, NULL);
	/* Set flag in context to require peer (server) certificate verification */
	SSL_CTX_set_verify(ctx, DbgSimCfg::Instance().GmsslVerifyMode.Data(), NULL);
	/* Load the  CA certificate into the SSL_CTX structure */
	/* This will allow this client to verify the server's certificate. */
	int ret = SSL_CTX_load_verify_locations(ctx, CA_CERT_FILE, NULL);
	if (ret < 0)
	{
		LogErr << "SSL_CTX_load_verify_locations failed.";
	}

	//载入客户端数字证书
	if (SSL_CTX_use_certificate_file(ctx, CLIENT_CERT_FILE, DbgSimCfg::Instance().GmsslCrtFormat.Data()) <= 0)
	{
		LogErr << "DbgConfigGmClientSsl CLIENT_CERT_FILE err.\n";
		return -1;
	}

	//载入客户端私钥
	if (SSL_CTX_use_PrivateKey_file(ctx, CLIENT_KEY_FILE, DbgSimCfg::Instance().GmsslCrtFormat.Data()) <= 0)
	{
		LogErr << "DbgConfigGmClientSsl CLIENT_KEY_FILE err.\n";
		return -1;
	}
	if (StrCmp(DbgSimCfg::Instance().GmsslLinkMode.StrData(), "SM2-WITH-SMS4-SM3") == 0)
	{
		//载入客户端加密证书
		if (SSL_CTX_use_certificate_file(ctx, CLIENT_ENC_CERT_FILE, DbgSimCfg::Instance().GmsslCrtFormat.Data()) <= 0)
		{
			LogErr << "SSL_CTX_use_certificate_file ENC_CERT_FILE err.\n";
			return(-1);
		}
		//载入加密私钥
		if (SSL_CTX_use_PrivateKey_file(ctx, CLIENT_ENC_KEY_FILE, DbgSimCfg::Instance().GmsslCrtFormat.Data()) <= 0)
		{
			LogErr << "SSL_CTX_use_PrivateKey_file ENC_KEY_FILE err.\n";
			return(-1);
		}
		//检查私钥是否正确
		if (SSL_CTX_check_private_key(ctx) <= 0)
		{
			LogErr << "SSL_CTX_check_private_key err.\n";
			return -1;
		}
	}
	return 0;
}
int32 spt::DbgGmSslClientIni()
{
	//gmssl双证书通信
	SSL_METHOD* meth = (SSL_METHOD*)GmClientMothed();

	if (!meth)
	{
		LogErr << "DbgGmSslClientIni meth is null.\n";
		return -1;
	}
	//建立新的SSL上下文 
	SSL_CTX* ctx = (SSL_CTX*)SslContextNew(meth);

	if (!ctx)
	{
		LogErr << "DbgGmSslClientIni ctx is null.\n";
		return -1;
	}

	if (DbgConfigGmClientSsl(ctx))
	{
		LogErr << "DbgGmSslClientIni DbgConfigGmClientSsl failed.\n";
		SSL_CTX_free(ctx);
		return -1;
	}
	if (DbgGmSslClientCtx)
	{
		SSL_CTX_free(DbgGmSslClientCtx);
	}
	DbgGmSslClientCtx = ctx;
	return 0;
}

void* spt::DbgGmSslSockServerNew(void* Sock)
{
	//TCP连接已经建立，将连接付给SSL
	SSL* ssl = SSL_new(DbgGmSslServerCtx);
	if (!ssl)
	{
		return 0;
	}
	//socket加入到ssl
	SSL_set_fd(ssl, (int)Sock);
	return ssl;
}

void* spt::DbgGmSslSockClientNew(void* Sock)
{
	//TCP连接已经建立，将连接付给SSL
	SSL* ssl = SSL_new(DbgGmSslClientCtx);
	if (!ssl)
	{
		return 0;
	}
	//socket加入到ssl
	SSL_set_fd(ssl, (int)Sock);
	return ssl;
}

int32 spt::DbgGmSslAccept(void* GmSock)
{
	if (!GmSock)
	{
		return -1;
	}
	int32 err = SSL_accept((SSL*)GmSock);
	if (err == 1)
	{
		LogMsg << "SSL_get_error SSL_ERROR_SSL\n";
		return 0;
	}
	else
	{
		//失败，根据错误码来判断
		err = SSL_get_error((SSL*)GmSock, err);
		if (err == SSL_ERROR_WANT_READ)
		{
			//	char buf[100] = { 0 };
			//	DbgGmSslRead(GmSock, buf, sizeof(buf));
			LogErr.Stamp() << "SSL_get_error SSL_ERROR_WANT_READ\n";
			return -1;
		}
		else if (err == SSL_ERROR_WANT_WRITE)
		{
			//	char buf[100] = { 0 };
			//	DbgGmSslWrite(GmSock, buf, sizeof(buf));
			LogErr.Stamp() << "SSL_get_error SSL_ERROR_WANT_WRITE\n";
			return -1;
		}
	}
	return -1;
}
int32 spt::DbgGmSslConnect(void* GmSock)
{
	if (!GmSock)
	{
		return -1;
	}
	int32 err = -1;
#ifdef WIN32_SIM
	err = SSL_connect((SSL*)GmSock);
#else 
	err = SSL_connect((SSL*)GmSock);
#endif
	if (err == 1)
	{
		return 0;
	}
	else
	{
		//失败，根据错误码来判断
		err = SSL_get_error((SSL*)GmSock, err);
		if (err == SSL_ERROR_WANT_READ)
		{
			//	char buf[100] = { 0 };
			//	DbgGmSslRead(GmSock, buf, sizeof(buf));
			return -1;
		}
		else if (err == SSL_ERROR_WANT_WRITE)
		{
			//	char buf[100] = { 0 };
			//	DbgGmSslWrite(GmSock, buf, sizeof(buf));
			return -1;
		}
	}
	return -1;
}
int32 spt::DbgGmSslClose(void* GmSock)
{
	SSL_shutdown((SSL*)GmSock);
	SSL_free((SSL*)GmSock);
	return 0;
}
int32 spt::DbgGmSslWrite(void* GmSock, const void* Buf, int32 BufLen)
{
	if (!GmSock)
	{
		return 0;
	}
#ifdef WIN32_SIM
	return SSL_write((SSL*)GmSock, Buf, BufLen);
#else
	return SSL_write((SSL*)GmSock, Buf, BufLen);
#endif // WIN32_SIM
}
int32 spt::DbgGmSslRead(void* GmSock, void* Buf, int32 BufLen)
{
	if (!GmSock)
	{
		return 0;
	}
#ifdef WIN32_SIM
	return SSL_read((SSL*)GmSock, Buf, BufLen);
#else
	return SSL_read((SSL*)GmSock, Buf, BufLen);
#endif // WIN32_SIM
}

int32 spt::CheckDbgServerCrt()
{
	if (SptMain::Instance().StartMode() != SptMain::E_Normal)
	{
		return -1;
	}
	if (0 != Access(CA_CERT_FILE, 0))
	{
		char text[] =
		{
			 0x2D,0x2D,0x2D,0x2D,0x2D,0x42,0x45,0x47,0x49,0x4E,0x20,0x43,0x45,0x52,0x54,0x49,0x46,0x49,0x43,0x41,0x54,0x45,0x2D,0x2D,0x2D,0x2D,0x2D,0x0D,0x0A,0x4D,0x49,0x49,0x43,0x45,0x54,0x43,0x43,0x41,0x62,0x61,0x67,0x41,0x77,0x49,0x42,0x41,0x67,0x49,0x4A,0x41,0x4C,0x41,0x2F,0x4A,0x2B,0x5A,0x6B,0x73,0x44,0x64,0x55,0x4D,0x41,0x6F,0x47,0x43,0x43,0x71,0x42,0x48,0x4D,0x39,0x56,0x41,0x59,0x4E,0x31,0x4D,0x46,0x30,0x78,0x43,0x7A,0x41,0x4A,0x42,0x67,0x4E,0x56,0x42,0x41,0x59,0x54,0x0D,0x0A,0x41,0x6B,0x4E,0x4F,0x4D,0x51,0x73,0x77,0x43,0x51,0x59,0x44,0x56,0x51,0x51,0x49,0x44,0x41,0x4A,0x54,0x52,0x44,0x45,0x4C,0x4D,0x41,0x6B,0x47,0x41,0x31,0x55,0x45,0x42,0x77,0x77,0x43,0x53,0x6B,0x34,0x78,0x44,0x7A,0x41,0x4E,0x42,0x67,0x4E,0x56,0x42,0x41,0x6F,0x4D,0x42,0x6B,0x6C,0x46,0x55,0x30,0x78,0x42,0x51,0x6A,0x45,0x4C,0x0D,0x0A,0x4D,0x41,0x6B,0x47,0x41,0x31,0x55,0x45,0x43,0x77,0x77,0x43,0x55,0x6B,0x51,0x78,0x46,0x6A,0x41,0x55,0x42,0x67,0x4E,0x56,0x42,0x41,0x4D,0x4D,0x44,0x56,0x52,0x6C,0x63,0x33,0x51,0x67,0x51,0x30,0x45,0x67,0x4B,0x46,0x4E,0x4E,0x4D,0x69,0x6B,0x77,0x49,0x42,0x63,0x4E,0x4D,0x6A,0x45,0x77,0x4E,0x6A,0x41,0x30,0x4D,0x44,0x45,0x77,0x0D,0x0A,0x4D,0x6A,0x4D,0x7A,0x57,0x68,0x67,0x50,0x4D,0x7A,0x41,0x79,0x4D,0x44,0x45,0x77,0x4D,0x44,0x55,0x77,0x4D,0x54,0x41,0x79,0x4D,0x7A,0x4E,0x61,0x4D,0x46,0x30,0x78,0x43,0x7A,0x41,0x4A,0x42,0x67,0x4E,0x56,0x42,0x41,0x59,0x54,0x41,0x6B,0x4E,0x4F,0x4D,0x51,0x73,0x77,0x43,0x51,0x59,0x44,0x56,0x51,0x51,0x49,0x44,0x41,0x4A,0x54,0x0D,0x0A,0x52,0x44,0x45,0x4C,0x4D,0x41,0x6B,0x47,0x41,0x31,0x55,0x45,0x42,0x77,0x77,0x43,0x53,0x6B,0x34,0x78,0x44,0x7A,0x41,0x4E,0x42,0x67,0x4E,0x56,0x42,0x41,0x6F,0x4D,0x42,0x6B,0x6C,0x46,0x55,0x30,0x78,0x42,0x51,0x6A,0x45,0x4C,0x4D,0x41,0x6B,0x47,0x41,0x31,0x55,0x45,0x43,0x77,0x77,0x43,0x55,0x6B,0x51,0x78,0x46,0x6A,0x41,0x55,0x0D,0x0A,0x42,0x67,0x4E,0x56,0x42,0x41,0x4D,0x4D,0x44,0x56,0x52,0x6C,0x63,0x33,0x51,0x67,0x51,0x30,0x45,0x67,0x4B,0x46,0x4E,0x4E,0x4D,0x69,0x6B,0x77,0x57,0x54,0x41,0x54,0x42,0x67,0x63,0x71,0x68,0x6B,0x6A,0x4F,0x50,0x51,0x49,0x42,0x42,0x67,0x67,0x71,0x67,0x52,0x7A,0x50,0x56,0x51,0x47,0x43,0x4C,0x51,0x4E,0x43,0x41,0x41,0x54,0x6E,0x0D,0x0A,0x2B,0x75,0x69,0x50,0x61,0x65,0x2F,0x78,0x46,0x69,0x59,0x42,0x78,0x46,0x59,0x38,0x4B,0x6B,0x37,0x55,0x69,0x6A,0x73,0x6B,0x41,0x46,0x72,0x45,0x46,0x4E,0x38,0x4B,0x39,0x69,0x58,0x4E,0x34,0x32,0x6E,0x53,0x38,0x50,0x41,0x67,0x44,0x36,0x48,0x69,0x2B,0x75,0x35,0x70,0x6D,0x59,0x70,0x61,0x56,0x59,0x79,0x62,0x38,0x54,0x51,0x43,0x0D,0x0A,0x73,0x78,0x32,0x31,0x4E,0x2B,0x64,0x6D,0x4D,0x48,0x6E,0x51,0x4E,0x6B,0x42,0x66,0x70,0x5A,0x51,0x69,0x6F,0x31,0x30,0x77,0x57,0x7A,0x41,0x64,0x42,0x67,0x4E,0x56,0x48,0x51,0x34,0x45,0x46,0x67,0x51,0x55,0x49,0x35,0x6E,0x6F,0x39,0x59,0x35,0x71,0x43,0x79,0x37,0x56,0x49,0x79,0x52,0x61,0x61,0x4C,0x6A,0x59,0x32,0x4A,0x65,0x46,0x0D,0x0A,0x2F,0x46,0x38,0x77,0x48,0x77,0x59,0x44,0x56,0x52,0x30,0x6A,0x42,0x42,0x67,0x77,0x46,0x6F,0x41,0x55,0x49,0x35,0x6E,0x6F,0x39,0x59,0x35,0x71,0x43,0x79,0x37,0x56,0x49,0x79,0x52,0x61,0x61,0x4C,0x6A,0x59,0x32,0x4A,0x65,0x46,0x2F,0x46,0x38,0x77,0x44,0x41,0x59,0x44,0x56,0x52,0x30,0x54,0x42,0x41,0x55,0x77,0x41,0x77,0x45,0x42,0x0D,0x0A,0x2F,0x7A,0x41,0x4C,0x42,0x67,0x4E,0x56,0x48,0x51,0x38,0x45,0x42,0x41,0x4D,0x43,0x41,0x51,0x59,0x77,0x43,0x67,0x59,0x49,0x4B,0x6F,0x45,0x63,0x7A,0x31,0x55,0x42,0x67,0x33,0x55,0x44,0x53,0x51,0x41,0x77,0x52,0x67,0x49,0x68,0x41,0x49,0x58,0x4B,0x62,0x65,0x79,0x74,0x41,0x41,0x77,0x59,0x2F,0x43,0x44,0x30,0x47,0x63,0x72,0x2B,0x0D,0x0A,0x4D,0x58,0x6C,0x44,0x5A,0x37,0x4E,0x50,0x79,0x45,0x71,0x67,0x30,0x65,0x45,0x52,0x4E,0x6B,0x4E,0x44,0x77,0x4F,0x30,0x45,0x41,0x69,0x45,0x41,0x31,0x67,0x48,0x51,0x6A,0x72,0x67,0x6A,0x72,0x61,0x4C,0x79,0x6F,0x4E,0x73,0x48,0x56,0x52,0x58,0x34,0x34,0x79,0x61,0x35,0x77,0x4F,0x46,0x50,0x74,0x50,0x49,0x57,0x45,0x69,0x42,0x46,0x0D,0x0A,0x4B,0x52,0x55,0x6E,0x37,0x49,0x4D,0x3D,0x0D,0x0A,0x2D,0x2D,0x2D,0x2D,0x2D,0x45,0x4E,0x44,0x20,0x43,0x45,0x52,0x54,0x49,0x46,0x49,0x43,0x41,0x54,0x45,0x2D,0x2D,0x2D,0x2D,0x2D,0x0D,0x0A,
		};
		SalFile file;
		file.SetFullName(CA_CERT_FILE);
		file.Creat();
		file.Write(text, sizeof(text));
	}
	else if (0)
	{
		PrintFile2Hex(CA_CERT_FILE);
	}
	if (0 != Access(SIGN_CERT_FILE, 0))
	{
		char text[] =
		{
			 0x2D,0x2D,0x2D,0x2D,0x2D,0x42,0x45,0x47,0x49,0x4E,0x20,0x43,0x45,0x52,0x54,0x49,0x46,0x49,0x43,0x41,0x54,0x45,0x2D,0x2D,0x2D,0x2D,0x2D,0x0D,0x0A,0x4D,0x49,0x49,0x42,0x30,0x44,0x43,0x43,0x41,0x58,0x65,0x67,0x41,0x77,0x49,0x42,0x41,0x67,0x49,0x4A,0x41,0x49,0x63,0x2B,0x69,0x78,0x39,0x33,0x46,0x46,0x69,0x73,0x4D,0x41,0x6F,0x47,0x43,0x43,0x71,0x42,0x48,0x4D,0x39,0x56,0x41,0x59,0x4E,0x31,0x4D,0x46,0x30,0x78,0x43,0x7A,0x41,0x4A,0x42,0x67,0x4E,0x56,0x42,0x41,0x59,0x54,0x0D,0x0A,0x41,0x6B,0x4E,0x4F,0x4D,0x51,0x73,0x77,0x43,0x51,0x59,0x44,0x56,0x51,0x51,0x49,0x44,0x41,0x4A,0x54,0x52,0x44,0x45,0x4C,0x4D,0x41,0x6B,0x47,0x41,0x31,0x55,0x45,0x42,0x77,0x77,0x43,0x53,0x6B,0x34,0x78,0x44,0x7A,0x41,0x4E,0x42,0x67,0x4E,0x56,0x42,0x41,0x6F,0x4D,0x42,0x6B,0x6C,0x46,0x55,0x30,0x78,0x42,0x51,0x6A,0x45,0x4C,0x0D,0x0A,0x4D,0x41,0x6B,0x47,0x41,0x31,0x55,0x45,0x43,0x77,0x77,0x43,0x55,0x6B,0x51,0x78,0x46,0x6A,0x41,0x55,0x42,0x67,0x4E,0x56,0x42,0x41,0x4D,0x4D,0x44,0x56,0x52,0x6C,0x63,0x33,0x51,0x67,0x51,0x30,0x45,0x67,0x4B,0x46,0x4E,0x4E,0x4D,0x69,0x6B,0x77,0x49,0x42,0x63,0x4E,0x4D,0x6A,0x45,0x77,0x4E,0x6A,0x41,0x30,0x4D,0x44,0x45,0x77,0x0D,0x0A,0x4D,0x6A,0x4D,0x7A,0x57,0x68,0x67,0x50,0x4D,0x7A,0x41,0x79,0x4D,0x44,0x45,0x77,0x4D,0x44,0x55,0x77,0x4D,0x54,0x41,0x79,0x4D,0x7A,0x4E,0x61,0x4D,0x47,0x45,0x78,0x43,0x7A,0x41,0x4A,0x42,0x67,0x4E,0x56,0x42,0x41,0x59,0x54,0x41,0x6B,0x4E,0x4F,0x4D,0x51,0x73,0x77,0x43,0x51,0x59,0x44,0x56,0x51,0x51,0x49,0x44,0x41,0x4A,0x54,0x0D,0x0A,0x52,0x44,0x45,0x4C,0x4D,0x41,0x6B,0x47,0x41,0x31,0x55,0x45,0x42,0x77,0x77,0x43,0x53,0x6B,0x34,0x78,0x44,0x7A,0x41,0x4E,0x42,0x67,0x4E,0x56,0x42,0x41,0x6F,0x4D,0x42,0x6B,0x6C,0x46,0x55,0x30,0x78,0x42,0x51,0x6A,0x45,0x4C,0x4D,0x41,0x6B,0x47,0x41,0x31,0x55,0x45,0x43,0x77,0x77,0x43,0x55,0x6B,0x51,0x78,0x47,0x6A,0x41,0x59,0x0D,0x0A,0x42,0x67,0x4E,0x56,0x42,0x41,0x4D,0x4D,0x45,0x58,0x4E,0x6C,0x63,0x6E,0x5A,0x6C,0x63,0x69,0x42,0x7A,0x61,0x57,0x64,0x75,0x49,0x43,0x68,0x54,0x54,0x54,0x49,0x70,0x4D,0x46,0x6B,0x77,0x45,0x77,0x59,0x48,0x4B,0x6F,0x5A,0x49,0x7A,0x6A,0x30,0x43,0x41,0x51,0x59,0x49,0x4B,0x6F,0x45,0x63,0x7A,0x31,0x55,0x42,0x67,0x69,0x30,0x44,0x0D,0x0A,0x51,0x67,0x41,0x45,0x4B,0x59,0x66,0x54,0x6F,0x56,0x30,0x35,0x48,0x5A,0x6F,0x4F,0x69,0x72,0x73,0x62,0x71,0x66,0x53,0x48,0x62,0x65,0x41,0x70,0x48,0x53,0x55,0x62,0x53,0x6D,0x65,0x38,0x52,0x6D,0x4F,0x65,0x62,0x72,0x4E,0x64,0x59,0x56,0x44,0x49,0x34,0x6C,0x4B,0x7A,0x49,0x6C,0x69,0x75,0x41,0x6B,0x63,0x47,0x33,0x30,0x79,0x46,0x0D,0x0A,0x50,0x33,0x4F,0x39,0x2F,0x77,0x65,0x4F,0x54,0x2F,0x68,0x6D,0x75,0x4C,0x58,0x54,0x5A,0x36,0x50,0x57,0x4F,0x6B,0x72,0x30,0x52,0x71,0x4D,0x61,0x4D,0x42,0x67,0x77,0x43,0x51,0x59,0x44,0x56,0x52,0x30,0x54,0x42,0x41,0x49,0x77,0x41,0x44,0x41,0x4C,0x42,0x67,0x4E,0x56,0x48,0x51,0x38,0x45,0x42,0x41,0x4D,0x43,0x42,0x73,0x41,0x77,0x0D,0x0A,0x43,0x67,0x59,0x49,0x4B,0x6F,0x45,0x63,0x7A,0x31,0x55,0x42,0x67,0x33,0x55,0x44,0x52,0x77,0x41,0x77,0x52,0x41,0x49,0x67,0x58,0x6E,0x6F,0x77,0x47,0x54,0x69,0x69,0x65,0x38,0x47,0x59,0x49,0x62,0x53,0x71,0x54,0x79,0x59,0x36,0x75,0x2F,0x52,0x68,0x62,0x2F,0x2B,0x65,0x4E,0x4D,0x79,0x51,0x42,0x41,0x2B,0x4E,0x57,0x6A,0x6D,0x69,0x0D,0x0A,0x2B,0x6F,0x63,0x43,0x49,0x48,0x42,0x49,0x39,0x48,0x4B,0x70,0x66,0x77,0x5A,0x66,0x57,0x71,0x51,0x73,0x76,0x4A,0x6A,0x36,0x76,0x58,0x78,0x75,0x76,0x6E,0x7A,0x57,0x31,0x67,0x58,0x71,0x2F,0x76,0x69,0x67,0x75,0x73,0x35,0x6B,0x52,0x77,0x74,0x69,0x0D,0x0A,0x2D,0x2D,0x2D,0x2D,0x2D,0x45,0x4E,0x44,0x20,0x43,0x45,0x52,0x54,0x49,0x46,0x49,0x43,0x41,0x54,0x45,0x2D,0x2D,0x2D,0x2D,0x2D,0x0D,0x0A,
		};
		SalFile file;
		file.SetFullName(SIGN_CERT_FILE);
		file.Creat();
		file.Write(text, sizeof(text));
	}
	else if (0)
	{
		PrintFile2Hex(SIGN_CERT_FILE);
	}
	if (0 != Access(SIGN_KEY_FILE, 0))
	{
		char text[] =
		{
			 0x2D,0x2D,0x2D,0x2D,0x2D,0x42,0x45,0x47,0x49,0x4E,0x20,0x50,0x52,0x49,0x56,0x41,0x54,0x45,0x20,0x4B,0x45,0x59,0x2D,0x2D,0x2D,0x2D,0x2D,0x0D,0x0A,0x4D,0x49,0x47,0x48,0x41,0x67,0x45,0x41,0x4D,0x42,0x4D,0x47,0x42,0x79,0x71,0x47,0x53,0x4D,0x34,0x39,0x41,0x67,0x45,0x47,0x43,0x43,0x71,0x42,0x48,0x4D,0x39,0x56,0x41,0x59,0x49,0x74,0x42,0x47,0x30,0x77,0x61,0x77,0x49,0x42,0x41,0x51,0x51,0x67,0x67,0x50,0x39,0x75,0x42,0x64,0x4B,0x30,0x67,0x57,0x71,0x43,0x73,0x53,0x42,0x76,0x0D,0x0A,0x51,0x6D,0x32,0x76,0x71,0x73,0x75,0x32,0x39,0x50,0x6B,0x75,0x6C,0x39,0x5A,0x54,0x46,0x62,0x79,0x5A,0x61,0x4C,0x58,0x46,0x65,0x57,0x6D,0x68,0x52,0x41,0x4E,0x43,0x41,0x41,0x51,0x70,0x68,0x39,0x4F,0x68,0x58,0x54,0x6B,0x64,0x6D,0x67,0x36,0x4B,0x75,0x78,0x75,0x70,0x39,0x49,0x64,0x74,0x34,0x43,0x6B,0x64,0x4A,0x52,0x74,0x4B,0x0D,0x0A,0x5A,0x37,0x78,0x47,0x59,0x35,0x35,0x75,0x73,0x31,0x31,0x68,0x55,0x4D,0x6A,0x69,0x55,0x72,0x4D,0x69,0x57,0x4B,0x34,0x43,0x52,0x77,0x62,0x66,0x54,0x49,0x55,0x2F,0x63,0x37,0x33,0x2F,0x42,0x34,0x35,0x50,0x2B,0x47,0x61,0x34,0x74,0x64,0x4E,0x6E,0x6F,0x39,0x59,0x36,0x53,0x76,0x52,0x47,0x0D,0x0A,0x2D,0x2D,0x2D,0x2D,0x2D,0x45,0x4E,0x44,0x20,0x50,0x52,0x49,0x56,0x41,0x54,0x45,0x20,0x4B,0x45,0x59,0x2D,0x2D,0x2D,0x2D,0x2D,0x0D,0x0A,
		};
		SalFile file;
		file.SetFullName(SIGN_KEY_FILE);
		file.Creat();
		file.Write(text, sizeof(text));
	}
	else if (0)
	{
		PrintFile2Hex(SIGN_KEY_FILE);
	}
	if (0 != Access(ENC_CERT_FILE, 0))
	{
		char text[] =
		{
			 0x2D,0x2D,0x2D,0x2D,0x2D,0x42,0x45,0x47,0x49,0x4E,0x20,0x43,0x45,0x52,0x54,0x49,0x46,0x49,0x43,0x41,0x54,0x45,0x2D,0x2D,0x2D,0x2D,0x2D,0x0D,0x0A,0x4D,0x49,0x49,0x42,0x30,0x44,0x43,0x43,0x41,0x58,0x61,0x67,0x41,0x77,0x49,0x42,0x41,0x67,0x49,0x4A,0x41,0x49,0x63,0x2B,0x69,0x78,0x39,0x33,0x46,0x46,0x69,0x74,0x4D,0x41,0x6F,0x47,0x43,0x43,0x71,0x42,0x48,0x4D,0x39,0x56,0x41,0x59,0x4E,0x31,0x4D,0x46,0x30,0x78,0x43,0x7A,0x41,0x4A,0x42,0x67,0x4E,0x56,0x42,0x41,0x59,0x54,0x0D,0x0A,0x41,0x6B,0x4E,0x4F,0x4D,0x51,0x73,0x77,0x43,0x51,0x59,0x44,0x56,0x51,0x51,0x49,0x44,0x41,0x4A,0x54,0x52,0x44,0x45,0x4C,0x4D,0x41,0x6B,0x47,0x41,0x31,0x55,0x45,0x42,0x77,0x77,0x43,0x53,0x6B,0x34,0x78,0x44,0x7A,0x41,0x4E,0x42,0x67,0x4E,0x56,0x42,0x41,0x6F,0x4D,0x42,0x6B,0x6C,0x46,0x55,0x30,0x78,0x42,0x51,0x6A,0x45,0x4C,0x0D,0x0A,0x4D,0x41,0x6B,0x47,0x41,0x31,0x55,0x45,0x43,0x77,0x77,0x43,0x55,0x6B,0x51,0x78,0x46,0x6A,0x41,0x55,0x42,0x67,0x4E,0x56,0x42,0x41,0x4D,0x4D,0x44,0x56,0x52,0x6C,0x63,0x33,0x51,0x67,0x51,0x30,0x45,0x67,0x4B,0x46,0x4E,0x4E,0x4D,0x69,0x6B,0x77,0x49,0x42,0x63,0x4E,0x4D,0x6A,0x45,0x77,0x4E,0x6A,0x41,0x30,0x4D,0x44,0x45,0x77,0x0D,0x0A,0x4D,0x6A,0x4D,0x7A,0x57,0x68,0x67,0x50,0x4D,0x7A,0x41,0x79,0x4D,0x44,0x45,0x77,0x4D,0x44,0x55,0x77,0x4D,0x54,0x41,0x79,0x4D,0x7A,0x4E,0x61,0x4D,0x47,0x41,0x78,0x43,0x7A,0x41,0x4A,0x42,0x67,0x4E,0x56,0x42,0x41,0x59,0x54,0x41,0x6B,0x4E,0x4F,0x4D,0x51,0x73,0x77,0x43,0x51,0x59,0x44,0x56,0x51,0x51,0x49,0x44,0x41,0x4A,0x54,0x0D,0x0A,0x52,0x44,0x45,0x4C,0x4D,0x41,0x6B,0x47,0x41,0x31,0x55,0x45,0x42,0x77,0x77,0x43,0x53,0x6B,0x34,0x78,0x44,0x7A,0x41,0x4E,0x42,0x67,0x4E,0x56,0x42,0x41,0x6F,0x4D,0x42,0x6B,0x6C,0x46,0x55,0x30,0x78,0x42,0x51,0x6A,0x45,0x4C,0x4D,0x41,0x6B,0x47,0x41,0x31,0x55,0x45,0x43,0x77,0x77,0x43,0x55,0x6B,0x51,0x78,0x47,0x54,0x41,0x58,0x0D,0x0A,0x42,0x67,0x4E,0x56,0x42,0x41,0x4D,0x4D,0x45,0x48,0x4E,0x6C,0x63,0x6E,0x5A,0x6C,0x63,0x69,0x42,0x6C,0x62,0x6D,0x4D,0x67,0x4B,0x46,0x4E,0x4E,0x4D,0x69,0x6B,0x77,0x57,0x54,0x41,0x54,0x42,0x67,0x63,0x71,0x68,0x6B,0x6A,0x4F,0x50,0x51,0x49,0x42,0x42,0x67,0x67,0x71,0x67,0x52,0x7A,0x50,0x56,0x51,0x47,0x43,0x4C,0x51,0x4E,0x43,0x0D,0x0A,0x41,0x41,0x53,0x41,0x74,0x69,0x44,0x50,0x64,0x41,0x38,0x5A,0x74,0x56,0x66,0x70,0x73,0x49,0x58,0x44,0x37,0x79,0x41,0x30,0x69,0x68,0x76,0x54,0x38,0x72,0x48,0x62,0x41,0x54,0x51,0x63,0x34,0x69,0x53,0x73,0x7A,0x70,0x6B,0x32,0x55,0x6C,0x6D,0x75,0x32,0x47,0x6B,0x57,0x75,0x6D,0x33,0x6B,0x71,0x49,0x30,0x58,0x54,0x61,0x6C,0x6F,0x0D,0x0A,0x6C,0x32,0x43,0x4F,0x69,0x71,0x68,0x36,0x51,0x7A,0x41,0x55,0x74,0x34,0x66,0x34,0x47,0x31,0x6B,0x4E,0x62,0x6A,0x48,0x76,0x6F,0x78,0x6F,0x77,0x47,0x44,0x41,0x4A,0x42,0x67,0x4E,0x56,0x48,0x52,0x4D,0x45,0x41,0x6A,0x41,0x41,0x4D,0x41,0x73,0x47,0x41,0x31,0x55,0x64,0x44,0x77,0x51,0x45,0x41,0x77,0x49,0x44,0x4F,0x44,0x41,0x4B,0x0D,0x0A,0x42,0x67,0x67,0x71,0x67,0x52,0x7A,0x50,0x56,0x51,0x47,0x44,0x64,0x51,0x4E,0x49,0x41,0x44,0x42,0x46,0x41,0x69,0x45,0x41,0x69,0x64,0x6D,0x47,0x74,0x4F,0x66,0x37,0x6F,0x30,0x6B,0x64,0x79,0x6C,0x2F,0x67,0x58,0x62,0x66,0x53,0x74,0x52,0x6B,0x76,0x61,0x68,0x4C,0x65,0x2B,0x76,0x51,0x66,0x73,0x4C,0x68,0x32,0x6C,0x49,0x46,0x67,0x0D,0x0A,0x5A,0x47,0x34,0x43,0x49,0x47,0x69,0x72,0x74,0x63,0x79,0x7A,0x48,0x78,0x7A,0x66,0x53,0x49,0x72,0x71,0x4D,0x44,0x77,0x63,0x51,0x68,0x4B,0x6A,0x65,0x62,0x4D,0x6E,0x45,0x58,0x6B,0x6C,0x67,0x6F,0x64,0x69,0x4D,0x63,0x6E,0x47,0x50,0x7A,0x78,0x6C,0x0D,0x0A,0x2D,0x2D,0x2D,0x2D,0x2D,0x45,0x4E,0x44,0x20,0x43,0x45,0x52,0x54,0x49,0x46,0x49,0x43,0x41,0x54,0x45,0x2D,0x2D,0x2D,0x2D,0x2D,0x0D,0x0A,
		};
		SalFile file;
		file.SetFullName(ENC_CERT_FILE);
		file.Creat();
		file.Write(text, sizeof(text));
	}
	else if (0)
	{
		PrintFile2Hex(ENC_CERT_FILE);
	}
	if (0 != Access(ENC_KEY_FILE, 0))
	{
		char text[] =
		{
			 0x2D,0x2D,0x2D,0x2D,0x2D,0x42,0x45,0x47,0x49,0x4E,0x20,0x50,0x52,0x49,0x56,0x41,0x54,0x45,0x20,0x4B,0x45,0x59,0x2D,0x2D,0x2D,0x2D,0x2D,0x0D,0x0A,0x4D,0x49,0x47,0x48,0x41,0x67,0x45,0x41,0x4D,0x42,0x4D,0x47,0x42,0x79,0x71,0x47,0x53,0x4D,0x34,0x39,0x41,0x67,0x45,0x47,0x43,0x43,0x71,0x42,0x48,0x4D,0x39,0x56,0x41,0x59,0x49,0x74,0x42,0x47,0x30,0x77,0x61,0x77,0x49,0x42,0x41,0x51,0x51,0x67,0x7A,0x66,0x47,0x53,0x49,0x42,0x43,0x68,0x64,0x44,0x6D,0x34,0x67,0x67,0x72,0x4C,0x0D,0x0A,0x77,0x6C,0x55,0x39,0x79,0x6E,0x32,0x61,0x31,0x55,0x72,0x77,0x32,0x43,0x77,0x44,0x51,0x6F,0x54,0x79,0x59,0x36,0x48,0x7A,0x52,0x4D,0x61,0x68,0x52,0x41,0x4E,0x43,0x41,0x41,0x53,0x41,0x74,0x69,0x44,0x50,0x64,0x41,0x38,0x5A,0x74,0x56,0x66,0x70,0x73,0x49,0x58,0x44,0x37,0x79,0x41,0x30,0x69,0x68,0x76,0x54,0x38,0x72,0x48,0x62,0x0D,0x0A,0x41,0x54,0x51,0x63,0x34,0x69,0x53,0x73,0x7A,0x70,0x6B,0x32,0x55,0x6C,0x6D,0x75,0x32,0x47,0x6B,0x57,0x75,0x6D,0x33,0x6B,0x71,0x49,0x30,0x58,0x54,0x61,0x6C,0x6F,0x6C,0x32,0x43,0x4F,0x69,0x71,0x68,0x36,0x51,0x7A,0x41,0x55,0x74,0x34,0x66,0x34,0x47,0x31,0x6B,0x4E,0x62,0x6A,0x48,0x76,0x0D,0x0A,0x2D,0x2D,0x2D,0x2D,0x2D,0x45,0x4E,0x44,0x20,0x50,0x52,0x49,0x56,0x41,0x54,0x45,0x20,0x4B,0x45,0x59,0x2D,0x2D,0x2D,0x2D,0x2D,0x0D,0x0A,
		};
		SalFile file;
		file.SetFullName(ENC_KEY_FILE);
		file.Creat();
		file.Write(text, sizeof(text));
	}
	else if (0)
	{
		PrintFile2Hex(ENC_KEY_FILE);
	}

	return 0;
}

int32 spt::CheckDbgClientCrt()
{
	if (SptMain::Instance().StartMode() != SptMain::E_Normal)
	{
		return -1;
	}
	if (0 != Access(CA_CERT_FILE, 0))
	{
		char text[] =
		{
			0x2D,0x2D,0x2D,0x2D,0x2D,0x42,0x45,0x47,0x49,0x4E,0x20,0x43,0x45,0x52,0x54,0x49,0x46,0x49,0x43,0x41,0x54,0x45,0x2D,0x2D,0x2D,0x2D,0x2D,0x0D,0x0A,0x4D,0x49,0x49,0x43,0x45,0x54,0x43,0x43,0x41,0x62,0x61,0x67,0x41,0x77,0x49,0x42,0x41,0x67,0x49,0x4A,0x41,0x4C,0x41,0x2F,0x4A,0x2B,0x5A,0x6B,0x73,0x44,0x64,0x55,0x4D,0x41,0x6F,0x47,0x43,0x43,0x71,0x42,0x48,0x4D,0x39,0x56,0x41,0x59,0x4E,0x31,0x4D,0x46,0x30,0x78,0x43,0x7A,0x41,0x4A,0x42,0x67,0x4E,0x56,0x42,0x41,0x59,0x54,0x0D,0x0A,0x41,0x6B,0x4E,0x4F,0x4D,0x51,0x73,0x77,0x43,0x51,0x59,0x44,0x56,0x51,0x51,0x49,0x44,0x41,0x4A,0x54,0x52,0x44,0x45,0x4C,0x4D,0x41,0x6B,0x47,0x41,0x31,0x55,0x45,0x42,0x77,0x77,0x43,0x53,0x6B,0x34,0x78,0x44,0x7A,0x41,0x4E,0x42,0x67,0x4E,0x56,0x42,0x41,0x6F,0x4D,0x42,0x6B,0x6C,0x46,0x55,0x30,0x78,0x42,0x51,0x6A,0x45,0x4C,0x0D,0x0A,0x4D,0x41,0x6B,0x47,0x41,0x31,0x55,0x45,0x43,0x77,0x77,0x43,0x55,0x6B,0x51,0x78,0x46,0x6A,0x41,0x55,0x42,0x67,0x4E,0x56,0x42,0x41,0x4D,0x4D,0x44,0x56,0x52,0x6C,0x63,0x33,0x51,0x67,0x51,0x30,0x45,0x67,0x4B,0x46,0x4E,0x4E,0x4D,0x69,0x6B,0x77,0x49,0x42,0x63,0x4E,0x4D,0x6A,0x45,0x77,0x4E,0x6A,0x41,0x30,0x4D,0x44,0x45,0x77,0x0D,0x0A,0x4D,0x6A,0x4D,0x7A,0x57,0x68,0x67,0x50,0x4D,0x7A,0x41,0x79,0x4D,0x44,0x45,0x77,0x4D,0x44,0x55,0x77,0x4D,0x54,0x41,0x79,0x4D,0x7A,0x4E,0x61,0x4D,0x46,0x30,0x78,0x43,0x7A,0x41,0x4A,0x42,0x67,0x4E,0x56,0x42,0x41,0x59,0x54,0x41,0x6B,0x4E,0x4F,0x4D,0x51,0x73,0x77,0x43,0x51,0x59,0x44,0x56,0x51,0x51,0x49,0x44,0x41,0x4A,0x54,0x0D,0x0A,0x52,0x44,0x45,0x4C,0x4D,0x41,0x6B,0x47,0x41,0x31,0x55,0x45,0x42,0x77,0x77,0x43,0x53,0x6B,0x34,0x78,0x44,0x7A,0x41,0x4E,0x42,0x67,0x4E,0x56,0x42,0x41,0x6F,0x4D,0x42,0x6B,0x6C,0x46,0x55,0x30,0x78,0x42,0x51,0x6A,0x45,0x4C,0x4D,0x41,0x6B,0x47,0x41,0x31,0x55,0x45,0x43,0x77,0x77,0x43,0x55,0x6B,0x51,0x78,0x46,0x6A,0x41,0x55,0x0D,0x0A,0x42,0x67,0x4E,0x56,0x42,0x41,0x4D,0x4D,0x44,0x56,0x52,0x6C,0x63,0x33,0x51,0x67,0x51,0x30,0x45,0x67,0x4B,0x46,0x4E,0x4E,0x4D,0x69,0x6B,0x77,0x57,0x54,0x41,0x54,0x42,0x67,0x63,0x71,0x68,0x6B,0x6A,0x4F,0x50,0x51,0x49,0x42,0x42,0x67,0x67,0x71,0x67,0x52,0x7A,0x50,0x56,0x51,0x47,0x43,0x4C,0x51,0x4E,0x43,0x41,0x41,0x54,0x6E,0x0D,0x0A,0x2B,0x75,0x69,0x50,0x61,0x65,0x2F,0x78,0x46,0x69,0x59,0x42,0x78,0x46,0x59,0x38,0x4B,0x6B,0x37,0x55,0x69,0x6A,0x73,0x6B,0x41,0x46,0x72,0x45,0x46,0x4E,0x38,0x4B,0x39,0x69,0x58,0x4E,0x34,0x32,0x6E,0x53,0x38,0x50,0x41,0x67,0x44,0x36,0x48,0x69,0x2B,0x75,0x35,0x70,0x6D,0x59,0x70,0x61,0x56,0x59,0x79,0x62,0x38,0x54,0x51,0x43,0x0D,0x0A,0x73,0x78,0x32,0x31,0x4E,0x2B,0x64,0x6D,0x4D,0x48,0x6E,0x51,0x4E,0x6B,0x42,0x66,0x70,0x5A,0x51,0x69,0x6F,0x31,0x30,0x77,0x57,0x7A,0x41,0x64,0x42,0x67,0x4E,0x56,0x48,0x51,0x34,0x45,0x46,0x67,0x51,0x55,0x49,0x35,0x6E,0x6F,0x39,0x59,0x35,0x71,0x43,0x79,0x37,0x56,0x49,0x79,0x52,0x61,0x61,0x4C,0x6A,0x59,0x32,0x4A,0x65,0x46,0x0D,0x0A,0x2F,0x46,0x38,0x77,0x48,0x77,0x59,0x44,0x56,0x52,0x30,0x6A,0x42,0x42,0x67,0x77,0x46,0x6F,0x41,0x55,0x49,0x35,0x6E,0x6F,0x39,0x59,0x35,0x71,0x43,0x79,0x37,0x56,0x49,0x79,0x52,0x61,0x61,0x4C,0x6A,0x59,0x32,0x4A,0x65,0x46,0x2F,0x46,0x38,0x77,0x44,0x41,0x59,0x44,0x56,0x52,0x30,0x54,0x42,0x41,0x55,0x77,0x41,0x77,0x45,0x42,0x0D,0x0A,0x2F,0x7A,0x41,0x4C,0x42,0x67,0x4E,0x56,0x48,0x51,0x38,0x45,0x42,0x41,0x4D,0x43,0x41,0x51,0x59,0x77,0x43,0x67,0x59,0x49,0x4B,0x6F,0x45,0x63,0x7A,0x31,0x55,0x42,0x67,0x33,0x55,0x44,0x53,0x51,0x41,0x77,0x52,0x67,0x49,0x68,0x41,0x49,0x58,0x4B,0x62,0x65,0x79,0x74,0x41,0x41,0x77,0x59,0x2F,0x43,0x44,0x30,0x47,0x63,0x72,0x2B,0x0D,0x0A,0x4D,0x58,0x6C,0x44,0x5A,0x37,0x4E,0x50,0x79,0x45,0x71,0x67,0x30,0x65,0x45,0x52,0x4E,0x6B,0x4E,0x44,0x77,0x4F,0x30,0x45,0x41,0x69,0x45,0x41,0x31,0x67,0x48,0x51,0x6A,0x72,0x67,0x6A,0x72,0x61,0x4C,0x79,0x6F,0x4E,0x73,0x48,0x56,0x52,0x58,0x34,0x34,0x79,0x61,0x35,0x77,0x4F,0x46,0x50,0x74,0x50,0x49,0x57,0x45,0x69,0x42,0x46,0x0D,0x0A,0x4B,0x52,0x55,0x6E,0x37,0x49,0x4D,0x3D,0x0D,0x0A,0x2D,0x2D,0x2D,0x2D,0x2D,0x45,0x4E,0x44,0x20,0x43,0x45,0x52,0x54,0x49,0x46,0x49,0x43,0x41,0x54,0x45,0x2D,0x2D,0x2D,0x2D,0x2D,0x0D,0x0A,
		};
		SalFile file;
		file.SetFullName(CA_CERT_FILE);
		file.Creat();
		file.Write(text, sizeof(text));
	}
	else if (0)
	{
		PrintFile2Hex(CA_CERT_FILE);
	}
	if (0 != Access(CLIENT_CERT_FILE, 0))
	{
		char text[] =
		{
			0x2D,0x2D,0x2D,0x2D,0x2D,0x42,0x45,0x47,0x49,0x4E,0x20,0x43,0x45,0x52,0x54,0x49,0x46,0x49,0x43,0x41,0x54,0x45,0x2D,0x2D,0x2D,0x2D,0x2D,0x0D,0x0A,0x4D,0x49,0x49,0x42,0x30,0x54,0x43,0x43,0x41,0x58,0x65,0x67,0x41,0x77,0x49,0x42,0x41,0x67,0x49,0x4A,0x41,0x49,0x63,0x2B,0x69,0x78,0x39,0x33,0x46,0x46,0x69,0x75,0x4D,0x41,0x6F,0x47,0x43,0x43,0x71,0x42,0x48,0x4D,0x39,0x56,0x41,0x59,0x4E,0x31,0x4D,0x46,0x30,0x78,0x43,0x7A,0x41,0x4A,0x42,0x67,0x4E,0x56,0x42,0x41,0x59,0x54,0x0D,0x0A,0x41,0x6B,0x4E,0x4F,0x4D,0x51,0x73,0x77,0x43,0x51,0x59,0x44,0x56,0x51,0x51,0x49,0x44,0x41,0x4A,0x54,0x52,0x44,0x45,0x4C,0x4D,0x41,0x6B,0x47,0x41,0x31,0x55,0x45,0x42,0x77,0x77,0x43,0x53,0x6B,0x34,0x78,0x44,0x7A,0x41,0x4E,0x42,0x67,0x4E,0x56,0x42,0x41,0x6F,0x4D,0x42,0x6B,0x6C,0x46,0x55,0x30,0x78,0x42,0x51,0x6A,0x45,0x4C,0x0D,0x0A,0x4D,0x41,0x6B,0x47,0x41,0x31,0x55,0x45,0x43,0x77,0x77,0x43,0x55,0x6B,0x51,0x78,0x46,0x6A,0x41,0x55,0x42,0x67,0x4E,0x56,0x42,0x41,0x4D,0x4D,0x44,0x56,0x52,0x6C,0x63,0x33,0x51,0x67,0x51,0x30,0x45,0x67,0x4B,0x46,0x4E,0x4E,0x4D,0x69,0x6B,0x77,0x49,0x42,0x63,0x4E,0x4D,0x6A,0x45,0x77,0x4E,0x6A,0x41,0x30,0x4D,0x44,0x45,0x77,0x0D,0x0A,0x4D,0x6A,0x4D,0x7A,0x57,0x68,0x67,0x50,0x4D,0x7A,0x41,0x79,0x4D,0x44,0x45,0x77,0x4D,0x44,0x55,0x77,0x4D,0x54,0x41,0x79,0x4D,0x7A,0x4E,0x61,0x4D,0x47,0x45,0x78,0x43,0x7A,0x41,0x4A,0x42,0x67,0x4E,0x56,0x42,0x41,0x59,0x54,0x41,0x6B,0x4E,0x4F,0x4D,0x51,0x73,0x77,0x43,0x51,0x59,0x44,0x56,0x51,0x51,0x49,0x44,0x41,0x4A,0x54,0x0D,0x0A,0x52,0x44,0x45,0x4C,0x4D,0x41,0x6B,0x47,0x41,0x31,0x55,0x45,0x42,0x77,0x77,0x43,0x53,0x6B,0x34,0x78,0x44,0x7A,0x41,0x4E,0x42,0x67,0x4E,0x56,0x42,0x41,0x6F,0x4D,0x42,0x6B,0x6C,0x46,0x55,0x30,0x78,0x42,0x51,0x6A,0x45,0x4C,0x4D,0x41,0x6B,0x47,0x41,0x31,0x55,0x45,0x43,0x77,0x77,0x43,0x55,0x6B,0x51,0x78,0x47,0x6A,0x41,0x59,0x0D,0x0A,0x42,0x67,0x4E,0x56,0x42,0x41,0x4D,0x4D,0x45,0x57,0x4E,0x73,0x61,0x57,0x56,0x75,0x64,0x43,0x42,0x7A,0x61,0x57,0x64,0x75,0x49,0x43,0x68,0x54,0x54,0x54,0x49,0x70,0x4D,0x46,0x6B,0x77,0x45,0x77,0x59,0x48,0x4B,0x6F,0x5A,0x49,0x7A,0x6A,0x30,0x43,0x41,0x51,0x59,0x49,0x4B,0x6F,0x45,0x63,0x7A,0x31,0x55,0x42,0x67,0x69,0x30,0x44,0x0D,0x0A,0x51,0x67,0x41,0x45,0x42,0x76,0x72,0x32,0x31,0x34,0x56,0x70,0x35,0x75,0x6B,0x72,0x39,0x41,0x56,0x2F,0x76,0x45,0x6A,0x71,0x32,0x2F,0x2B,0x68,0x39,0x44,0x68,0x6A,0x52,0x4A,0x37,0x49,0x6C,0x5A,0x39,0x74,0x77,0x54,0x55,0x77,0x35,0x44,0x2B,0x6E,0x33,0x39,0x54,0x61,0x7A,0x49,0x61,0x4F,0x30,0x5A,0x76,0x6D,0x6C,0x45,0x45,0x75,0x0D,0x0A,0x68,0x57,0x56,0x4A,0x68,0x51,0x30,0x41,0x55,0x39,0x37,0x51,0x74,0x7A,0x56,0x74,0x59,0x32,0x48,0x33,0x76,0x6C,0x43,0x59,0x55,0x71,0x4D,0x61,0x4D,0x42,0x67,0x77,0x43,0x51,0x59,0x44,0x56,0x52,0x30,0x54,0x42,0x41,0x49,0x77,0x41,0x44,0x41,0x4C,0x42,0x67,0x4E,0x56,0x48,0x51,0x38,0x45,0x42,0x41,0x4D,0x43,0x42,0x73,0x41,0x77,0x0D,0x0A,0x43,0x67,0x59,0x49,0x4B,0x6F,0x45,0x63,0x7A,0x31,0x55,0x42,0x67,0x33,0x55,0x44,0x53,0x41,0x41,0x77,0x52,0x51,0x49,0x68,0x41,0x4E,0x61,0x50,0x35,0x62,0x75,0x70,0x5A,0x55,0x67,0x30,0x4A,0x62,0x70,0x6B,0x63,0x51,0x57,0x77,0x52,0x38,0x53,0x53,0x49,0x62,0x7A,0x71,0x79,0x59,0x63,0x51,0x5A,0x4F,0x36,0x71,0x77,0x31,0x47,0x6C,0x0D,0x0A,0x50,0x6B,0x42,0x2F,0x41,0x69,0x41,0x4B,0x7A,0x5A,0x66,0x43,0x48,0x2F,0x67,0x52,0x54,0x44,0x79,0x79,0x6A,0x59,0x51,0x54,0x59,0x34,0x39,0x33,0x36,0x38,0x6D,0x35,0x36,0x66,0x4E,0x45,0x68,0x69,0x68,0x61,0x63,0x36,0x55,0x35,0x53,0x32,0x30,0x4C,0x45,0x77,0x3D,0x3D,0x0D,0x0A,0x2D,0x2D,0x2D,0x2D,0x2D,0x45,0x4E,0x44,0x20,0x43,0x45,0x52,0x54,0x49,0x46,0x49,0x43,0x41,0x54,0x45,0x2D,0x2D,0x2D,0x2D,0x2D,0x0D,0x0A,
		};
		SalFile file;
		file.SetFullName(CLIENT_CERT_FILE);
		file.Creat();
		file.Write(text, sizeof(text));
	}
	else if (0)
	{
		PrintFile2Hex(CLIENT_CERT_FILE);
	}
	if (0 != Access(CLIENT_KEY_FILE, 0))
	{
		char text[] =
		{
			0x2D,0x2D,0x2D,0x2D,0x2D,0x42,0x45,0x47,0x49,0x4E,0x20,0x50,0x52,0x49,0x56,0x41,0x54,0x45,0x20,0x4B,0x45,0x59,0x2D,0x2D,0x2D,0x2D,0x2D,0x0D,0x0A,0x4D,0x49,0x47,0x48,0x41,0x67,0x45,0x41,0x4D,0x42,0x4D,0x47,0x42,0x79,0x71,0x47,0x53,0x4D,0x34,0x39,0x41,0x67,0x45,0x47,0x43,0x43,0x71,0x42,0x48,0x4D,0x39,0x56,0x41,0x59,0x49,0x74,0x42,0x47,0x30,0x77,0x61,0x77,0x49,0x42,0x41,0x51,0x51,0x67,0x65,0x2B,0x33,0x74,0x77,0x78,0x2B,0x53,0x6F,0x67,0x71,0x6A,0x75,0x36,0x46,0x4E,0x0D,0x0A,0x4E,0x4F,0x72,0x2F,0x68,0x31,0x4F,0x4B,0x2B,0x43,0x6F,0x30,0x34,0x46,0x57,0x6C,0x61,0x58,0x39,0x62,0x6E,0x52,0x7A,0x6F,0x74,0x55,0x65,0x68,0x52,0x41,0x4E,0x43,0x41,0x41,0x51,0x47,0x2B,0x76,0x62,0x58,0x68,0x57,0x6E,0x6D,0x36,0x53,0x76,0x30,0x42,0x58,0x2B,0x38,0x53,0x4F,0x72,0x62,0x2F,0x36,0x48,0x30,0x4F,0x47,0x4E,0x45,0x0D,0x0A,0x6E,0x73,0x69,0x56,0x6E,0x32,0x33,0x42,0x4E,0x54,0x44,0x6B,0x50,0x36,0x66,0x66,0x31,0x4E,0x72,0x4D,0x68,0x6F,0x37,0x52,0x6D,0x2B,0x61,0x55,0x51,0x53,0x36,0x46,0x5A,0x55,0x6D,0x46,0x44,0x51,0x42,0x54,0x33,0x74,0x43,0x33,0x4E,0x57,0x31,0x6A,0x59,0x66,0x65,0x2B,0x55,0x4A,0x68,0x53,0x0D,0x0A,0x2D,0x2D,0x2D,0x2D,0x2D,0x45,0x4E,0x44,0x20,0x50,0x52,0x49,0x56,0x41,0x54,0x45,0x20,0x4B,0x45,0x59,0x2D,0x2D,0x2D,0x2D,0x2D,0x0D,0x0A,
		};
		SalFile file;
		file.SetFullName(CLIENT_KEY_FILE);
		file.Creat();
		file.Write(text, sizeof(text));
	}
	else if (0)
	{
		PrintFile2Hex(CLIENT_KEY_FILE);
	}
	if (0 != Access(CLIENT_ENC_CERT_FILE, 0))
	{
		char text[] =
		{
			0x2D,0x2D,0x2D,0x2D,0x2D,0x42,0x45,0x47,0x49,0x4E,0x20,0x43,0x45,0x52,0x54,0x49,0x46,0x49,0x43,0x41,0x54,0x45,0x2D,0x2D,0x2D,0x2D,0x2D,0x0D,0x0A,0x4D,0x49,0x49,0x42,0x30,0x54,0x43,0x43,0x41,0x58,0x61,0x67,0x41,0x77,0x49,0x42,0x41,0x67,0x49,0x4A,0x41,0x49,0x63,0x2B,0x69,0x78,0x39,0x33,0x46,0x46,0x69,0x76,0x4D,0x41,0x6F,0x47,0x43,0x43,0x71,0x42,0x48,0x4D,0x39,0x56,0x41,0x59,0x4E,0x31,0x4D,0x46,0x30,0x78,0x43,0x7A,0x41,0x4A,0x42,0x67,0x4E,0x56,0x42,0x41,0x59,0x54,0x0D,0x0A,0x41,0x6B,0x4E,0x4F,0x4D,0x51,0x73,0x77,0x43,0x51,0x59,0x44,0x56,0x51,0x51,0x49,0x44,0x41,0x4A,0x54,0x52,0x44,0x45,0x4C,0x4D,0x41,0x6B,0x47,0x41,0x31,0x55,0x45,0x42,0x77,0x77,0x43,0x53,0x6B,0x34,0x78,0x44,0x7A,0x41,0x4E,0x42,0x67,0x4E,0x56,0x42,0x41,0x6F,0x4D,0x42,0x6B,0x6C,0x46,0x55,0x30,0x78,0x42,0x51,0x6A,0x45,0x4C,0x0D,0x0A,0x4D,0x41,0x6B,0x47,0x41,0x31,0x55,0x45,0x43,0x77,0x77,0x43,0x55,0x6B,0x51,0x78,0x46,0x6A,0x41,0x55,0x42,0x67,0x4E,0x56,0x42,0x41,0x4D,0x4D,0x44,0x56,0x52,0x6C,0x63,0x33,0x51,0x67,0x51,0x30,0x45,0x67,0x4B,0x46,0x4E,0x4E,0x4D,0x69,0x6B,0x77,0x49,0x42,0x63,0x4E,0x4D,0x6A,0x45,0x77,0x4E,0x6A,0x41,0x30,0x4D,0x44,0x45,0x77,0x0D,0x0A,0x4D,0x6A,0x4D,0x30,0x57,0x68,0x67,0x50,0x4D,0x7A,0x41,0x79,0x4D,0x44,0x45,0x77,0x4D,0x44,0x55,0x77,0x4D,0x54,0x41,0x79,0x4D,0x7A,0x52,0x61,0x4D,0x47,0x41,0x78,0x43,0x7A,0x41,0x4A,0x42,0x67,0x4E,0x56,0x42,0x41,0x59,0x54,0x41,0x6B,0x4E,0x4F,0x4D,0x51,0x73,0x77,0x43,0x51,0x59,0x44,0x56,0x51,0x51,0x49,0x44,0x41,0x4A,0x54,0x0D,0x0A,0x52,0x44,0x45,0x4C,0x4D,0x41,0x6B,0x47,0x41,0x31,0x55,0x45,0x42,0x77,0x77,0x43,0x53,0x6B,0x34,0x78,0x44,0x7A,0x41,0x4E,0x42,0x67,0x4E,0x56,0x42,0x41,0x6F,0x4D,0x42,0x6B,0x6C,0x46,0x55,0x30,0x78,0x42,0x51,0x6A,0x45,0x4C,0x4D,0x41,0x6B,0x47,0x41,0x31,0x55,0x45,0x43,0x77,0x77,0x43,0x55,0x6B,0x51,0x78,0x47,0x54,0x41,0x58,0x0D,0x0A,0x42,0x67,0x4E,0x56,0x42,0x41,0x4D,0x4D,0x45,0x47,0x4E,0x73,0x61,0x57,0x56,0x75,0x64,0x43,0x42,0x6C,0x62,0x6D,0x4D,0x67,0x4B,0x46,0x4E,0x4E,0x4D,0x69,0x6B,0x77,0x57,0x54,0x41,0x54,0x42,0x67,0x63,0x71,0x68,0x6B,0x6A,0x4F,0x50,0x51,0x49,0x42,0x42,0x67,0x67,0x71,0x67,0x52,0x7A,0x50,0x56,0x51,0x47,0x43,0x4C,0x51,0x4E,0x43,0x0D,0x0A,0x41,0x41,0x51,0x33,0x69,0x72,0x6C,0x4F,0x64,0x78,0x7A,0x6C,0x75,0x4C,0x58,0x77,0x69,0x52,0x41,0x45,0x36,0x74,0x56,0x44,0x69,0x48,0x78,0x43,0x75,0x37,0x32,0x76,0x58,0x69,0x34,0x37,0x42,0x76,0x49,0x77,0x73,0x54,0x52,0x31,0x6C,0x46,0x6B,0x39,0x31,0x55,0x53,0x33,0x32,0x39,0x4A,0x4B,0x55,0x5A,0x61,0x74,0x2F,0x6D,0x70,0x4F,0x0D,0x0A,0x59,0x6D,0x6B,0x5A,0x2B,0x76,0x39,0x52,0x45,0x75,0x47,0x6C,0x64,0x72,0x31,0x46,0x35,0x38,0x31,0x75,0x30,0x6C,0x49,0x35,0x6F,0x78,0x6F,0x77,0x47,0x44,0x41,0x4A,0x42,0x67,0x4E,0x56,0x48,0x52,0x4D,0x45,0x41,0x6A,0x41,0x41,0x4D,0x41,0x73,0x47,0x41,0x31,0x55,0x64,0x44,0x77,0x51,0x45,0x41,0x77,0x49,0x44,0x4F,0x44,0x41,0x4B,0x0D,0x0A,0x42,0x67,0x67,0x71,0x67,0x52,0x7A,0x50,0x56,0x51,0x47,0x44,0x64,0x51,0x4E,0x4A,0x41,0x44,0x42,0x47,0x41,0x69,0x45,0x41,0x74,0x57,0x6B,0x6D,0x6D,0x2F,0x32,0x57,0x61,0x50,0x70,0x61,0x35,0x2F,0x61,0x35,0x6E,0x65,0x75,0x44,0x62,0x69,0x6D,0x69,0x63,0x7A,0x79,0x39,0x42,0x77,0x6E,0x4F,0x77,0x74,0x75,0x68,0x76,0x30,0x2F,0x75,0x0D,0x0A,0x74,0x75,0x34,0x43,0x49,0x51,0x44,0x2F,0x59,0x67,0x78,0x64,0x62,0x36,0x39,0x55,0x71,0x38,0x76,0x7A,0x47,0x41,0x66,0x4B,0x42,0x4B,0x4F,0x38,0x54,0x73,0x62,0x2F,0x49,0x7A,0x44,0x58,0x30,0x52,0x77,0x69,0x2B,0x32,0x67,0x63,0x31,0x5A,0x46,0x7A,0x33,0x67,0x3D,0x3D,0x0D,0x0A,0x2D,0x2D,0x2D,0x2D,0x2D,0x45,0x4E,0x44,0x20,0x43,0x45,0x52,0x54,0x49,0x46,0x49,0x43,0x41,0x54,0x45,0x2D,0x2D,0x2D,0x2D,0x2D,0x0D,0x0A,
		};
		SalFile file;
		file.SetFullName(CLIENT_ENC_CERT_FILE);
		file.Creat();
		file.Write(text, sizeof(text));
	}
	else if (0)
	{
		PrintFile2Hex(CLIENT_ENC_CERT_FILE);
	}
	if (0 != Access(CLIENT_ENC_KEY_FILE, 0))
	{
		char text[] =
		{
			0x2D,0x2D,0x2D,0x2D,0x2D,0x42,0x45,0x47,0x49,0x4E,0x20,0x50,0x52,0x49,0x56,0x41,0x54,0x45,0x20,0x4B,0x45,0x59,0x2D,0x2D,0x2D,0x2D,0x2D,0x0D,0x0A,0x4D,0x49,0x47,0x48,0x41,0x67,0x45,0x41,0x4D,0x42,0x4D,0x47,0x42,0x79,0x71,0x47,0x53,0x4D,0x34,0x39,0x41,0x67,0x45,0x47,0x43,0x43,0x71,0x42,0x48,0x4D,0x39,0x56,0x41,0x59,0x49,0x74,0x42,0x47,0x30,0x77,0x61,0x77,0x49,0x42,0x41,0x51,0x51,0x67,0x36,0x2B,0x50,0x79,0x45,0x61,0x41,0x53,0x6C,0x6E,0x67,0x62,0x39,0x73,0x74,0x59,0x0D,0x0A,0x72,0x57,0x30,0x2B,0x51,0x50,0x31,0x41,0x62,0x65,0x47,0x35,0x35,0x45,0x70,0x79,0x39,0x58,0x52,0x6F,0x48,0x76,0x79,0x4A,0x33,0x61,0x75,0x68,0x52,0x41,0x4E,0x43,0x41,0x41,0x51,0x33,0x69,0x72,0x6C,0x4F,0x64,0x78,0x7A,0x6C,0x75,0x4C,0x58,0x77,0x69,0x52,0x41,0x45,0x36,0x74,0x56,0x44,0x69,0x48,0x78,0x43,0x75,0x37,0x32,0x76,0x0D,0x0A,0x58,0x69,0x34,0x37,0x42,0x76,0x49,0x77,0x73,0x54,0x52,0x31,0x6C,0x46,0x6B,0x39,0x31,0x55,0x53,0x33,0x32,0x39,0x4A,0x4B,0x55,0x5A,0x61,0x74,0x2F,0x6D,0x70,0x4F,0x59,0x6D,0x6B,0x5A,0x2B,0x76,0x39,0x52,0x45,0x75,0x47,0x6C,0x64,0x72,0x31,0x46,0x35,0x38,0x31,0x75,0x30,0x6C,0x49,0x35,0x0D,0x0A,0x2D,0x2D,0x2D,0x2D,0x2D,0x45,0x4E,0x44,0x20,0x50,0x52,0x49,0x56,0x41,0x54,0x45,0x20,0x4B,0x45,0x59,0x2D,0x2D,0x2D,0x2D,0x2D,0x0D,0x0A,
		};
		SalFile file;
		file.SetFullName(CLIENT_ENC_KEY_FILE);
		file.Creat();
		file.Write(text, sizeof(text));
	}
	else if (0)
	{
		PrintFile2Hex(CLIENT_ENC_KEY_FILE);
	}
	return 0;
}

