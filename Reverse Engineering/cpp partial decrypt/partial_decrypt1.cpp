
void fun_10002ffe() {
    k = 0;
    w = 0;
    i = 0;
    do {
        asm("cdq");
        y = (w + 1) % 0x7e; // counter
        *(int32_t*)(ebp5 - 4) = y; // memory region
        tmp1 = *reinterpret_cast<uint8_t*>(decryption_key + y - 0x104);
        tmp2 = tmp1;
        asm("cdq");
        k = (uint32_t)((int32_t)(tmp2 + k) % 0x7e);
        tmp3 = *reinterpret_cast<int32_t*>(ebp10 - 4); // memory region
        tmp4 = *reinterpret_cast<uint8_t*>(decryption_key + k - 0x104); 
        *(int8_t*)(decryption_key + tmp3 - 0x104) = *reinterpret_cast<int8_t*>(&tmp4);
        *(uint8_t*)(ebp14 + k - 0x104) = tmp1; //memory region2?
        tmp5 = *reinterpret_cast<uint8_t*>(enc_config + (*reinterpret_cast<uint8_t*>(enc_config + tmp3 - 0x104) + tmp2) % 0x7e - 0x104);
        *(uint8_t*)(i + enc_config) = (uint8_t)(*reinterpret_cast<uint8_t*>(i + enc_config) ^ *reinterpret_cast<uint8_t*>(&tmp5));
        ++i;
        w = *reinterpret_cast<int32_t*>(ebp18 - 4); // memory region
    } while (i < 0x1970);
}
