#pragma constseg=LOG_ZONE
const unsigned char log_zone[48] = 
{
    // No data will be preset in second log zone
    // Instead log zone will be written using RD request in JCI session

    // values taken from response to '21 FE':
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
    
    // values taken from response to '21 FF':
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};
#pragma constseg=default

#pragma constseg=APPLI_STATE
const unsigned short appli_state = 0xFFF0U;
#pragma constseg=default

#pragma constseg=CHECKSUM

//#error "Set here the version checksum (taken from SIR):
// Checksum reported by transfor is LSB-MSB exchanged
const unsigned short checksum = 0x57C0U;

#pragma constseg=default

