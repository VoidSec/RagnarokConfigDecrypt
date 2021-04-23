int configDecrypt()
{
  int i; // edi
  int v1; // esi
  int y; // ecx
  int z; // esi
  unsigned __int8 v4; // bl
  int x; // ebx
  int k; // eax
  int w; // edi
  unsigned __int8 v8; // cl
  int v9; // edi
  char *v10; // esi
  int v11; // ebx
  char v13[256]; // [esp+Ch] [ebp-304h] BYREF
  char v14[256]; // [esp+10Ch] [ebp-204h] BYREF "comehereplz"
  char v15[256]; // [esp+20Ch] [ebp-104h] BYREF decryptionkey
  int v16; // [esp+30Ch] [ebp-4h]

  zeroingMemory(v13, 0, 256u);                  // Writing arg2 (esp+4) #arg 3 of bytes (esp+8) of memory starting at arg1 (ESP) addr
                                                // 1: [esp] 012FFBBC 
                                                // 2: [esp+4] 00000000 
                                                // 3: [esp+8] 00000100 
                                                // 
                                                // RETURN in EAX: 012FFBBC starting addr of the zeroed out memory
  zeroingMemory(v15, 0, 256u);                  // 1: [esp] 012FFDBC "0±…w"
                                                // 2: [esp+4] 00000000 
                                                // 3: [esp+8] 00000100 
                                                // 
  zeroingMemory(v14, 0, 256u);                  // 1: [esp] 012FFCBC 
                                                // 2: [esp+4] 00000000 
                                                // 3: [esp+8] 00000100 
                                                // 
  sub_10012980(v14, "comehereplz");             // 1: [esp] 012FFCBC 
                                                // 2: [esp+4] 100143BC "comehereplz"
                                                // 
                                                // write "comehereplz" at 012FFCBC
                                                // return addr of "comehereplz" nullterminator 
  i = 0;
  v1 = (int)length(v14);                        // return in EAX the length of "comehereplz" str at 012FFCBC
  for ( y = 0; y < 256; ++y )                   // 012FFDBC
  {
    v15[y] = y;
    v13[y] = v14[y % v1];
  }                                             // writes 24 times the string "comehereplz" at 012FFBBC
                                                // writes charset (00-FF) at 012FFDBC
  for ( z = 0; z < 256; ++z )
  {
    v4 = v15[z];                                // v15=charset array
    i = (i + (unsigned __int8)v13[z] + v4) % 126;// v13= "comehereplz" x 24 array
    v15[z] = v15[i];
    v15[i] = v4;
  }                                             // encryption key at 012FFDBC
  x = 0;
  k = 0;
  for ( w = 0; w < 6512; ++w )                  // config at 10017000
  {
    v16 = (k + 1) % 126;
    v8 = v15[v16];
    x = (v8 + x) % 126;
    v15[v16] = v15[x];
    v15[x] = v8;
    config[w] ^= v15[(v8 + (unsigned int)(unsigned __int8)v15[(k + 1) % 126]) % 126];
    k = v16;
  }
  v9 = sub_10012B90(config, "\\r\\n");          // verify config was extracted in the right manner
  v10 = config;
  if ( v9 )
  {
    v11 = sub_10012800(6512);
    do
    {
      sub_10012A70(v11, v10, v9 - (_DWORD)v10);
      sub_10012910(v11, "\r\n");
      v10 = &length("\\r\\n")[v9];
      v9 = sub_10012B90(v10, "\\r\\n");
    }
    while ( v9 );
    sub_10012A70(v11, v10, &unk_10018970 - (_UNKNOWN *)v10);
    sub_10012830(config, v11, 6512);
    if ( v11 )
      sub_100127A0(v11);
  }
  dword_1001AC14 = sub_10011A40(config);
  dword_1001AC10 = sub_10011A20(dword_1001AC14, &unk_10014370);
  dword_1001AC0C = sub_10011A20(dword_1001AC14, "value");
  dword_1001AC08 = sub_10011A20(dword_1001AC14, "language");
  dword_1001AC04 = sub_10011A20(dword_1001AC14, "path");
  dword_1001AC00 = sub_10011A20(dword_1001AC14, &unk_10014390);
  dword_1001ABFC = sub_10011A20(dword_1001AC14, "content");
  dword_1001ABF8 = sub_10011A20(dword_1001AC14, "white");
  dword_1001ABF4 = sub_10011A20(dword_1001AC14, "black");
  dword_1001ABF0 = sub_10011A20(dword_1001AC14, "proc");
  dword_1001ABEC = sub_10011A20(dword_1001AC14, "full");
  return sub_10004A20();
}
/* Orphan comments:
"comehereplz" string is loaded char by char
and put at 00FFF810 x 24 times
generate decryption key
decrypt config
config size
--------------------------
*/