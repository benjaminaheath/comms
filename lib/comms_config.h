// Util config
// #define PRINT_BIN
// #define PRINT_HEX
#define PRINT_DEC
// phy config
// #define PHY_CLEAR_CHANNEL
#define PHY_NOISY_CHANNEL
#define PHY_NOISE_FREQ 0.9 // probability of bit flip

// dll config
#define DLL_BUF_MAX 64
#define DLL_HEAD_BYTE 0xFF
#define DLL_FOOT_BYTE 0xFF
#define DLL_PAYLOAD_MAX 23
#define DLL_HEAD_BYTES 1
#define DLL_CONTROL_BYTES 2
#define DLL_ADDRESS_BYTES 2
#define DLL_LEN_BYTES 1
#define DLL_CHECKSUM_BYTES 2
#define DLL_FOOT_BYTES 1