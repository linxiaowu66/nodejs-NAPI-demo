#include <napi.h>
#include <openssl/md5.h>

using namespace Napi;

void openssl_md5(const char *data, int size, unsigned char *buf){
    MD5_CTX c;
    MD5_Init(&c);
    MD5_Update(&c,data,size);
    MD5_Final(buf,&c);
}

String GetMD5(const CallbackInfo& info) {
  Env env = info.Env();
  std::string password = info[0].As<String>().Utf8Value();
  //printf("md5 in str:%s %ld\n",password.c_str(),password.size());
  unsigned char hash[16];
  memset(hash,0,16);
  openssl_md5(password.c_str(),password.size(),hash);
  char tmp[3];
  char md5str[33]={};
  int i;
  for (i = 0; i < 16; i++){
    sprintf(tmp,"%02x",hash[i]);
    strcat(md5str,tmp);
  }
  return String::New(env, md5str,32);
}

Napi::Object  Init(Env env, Object exports) {
  exports.Set("md5", Function::New(env, GetMD5));
  return exports;
}
NODE_API_MODULE(addon, Init)
