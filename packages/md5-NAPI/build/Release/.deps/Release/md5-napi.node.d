cmd_Release/md5-napi.node := c++ -bundle -undefined dynamic_lookup -Wl,-no_pie -Wl,-search_paths_first -mmacosx-version-min=10.7 -arch x86_64 -L./Release -stdlib=libc++  -o Release/md5-napi.node Release/obj.target/md5-napi/src/init.o Release/nothing.a -lssl -lcrypto