#include <v8.h>
#include <string.h>
#include <node.h>
#include <openssl/md5.h>
#include <nan.h>
using v8::Local;
using v8::Object;
using v8::String;

using namespace Nan;

void openssl_md5(const char *data, int size, unsigned char *buf){
    MD5_CTX c;
    MD5_Init(&c);
    MD5_Update(&c,data,size);
    MD5_Final(buf,&c);
}

NAN_METHOD(md5){
    Nan::HandleScope scope;
    unsigned char hash[16];
    Nan::Utf8String nan_string(info[0]);
    std::string name(*nan_string);
    openssl_md5(name.c_str(), name.size(), hash);
    char tmp[3];
    char md5str[33]={};
    for( int i = 0 ; i < 16 ; i ++ ){
      sprintf(tmp, "%02x", hash[i]);
      strcat(md5str, tmp);
    }
    info.GetReturnValue().Set(New(md5str).ToLocalChecked());
}

void init (Local<Object> exports)
{
    Nan::HandleScope scope;
    Nan::SetMethod(exports, "md5", md5);
}

NODE_MODULE(addon, init);
