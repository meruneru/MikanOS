#include "error.hpp"

namespace {

}
namespace pci{

// CONFIG_ADDRESSレジスタのIOポートアドレス
const uint16_t kConfigAddress = 0x0cf8;
// CONFIG_DATAレジスタのIOポートアドレス
const uint16_t kConfigData = 0x0cfc;

/** @brief PCI デバイスを操作するための基礎データを格納する
 *
 * バス番号，デバイス番号，ファンクション番号はデバイスを特定するのに必須．
 * その他の情報は単に利便性のために加えてある．
 * */
struct Device
{
    uint8_t bus;
    uint8_t device;
    uint8_t function;
    uint8_t header_type;
};

// ScanAllBus()で見つけたdevice一覧
inline std::array<Device, 32> devices;
//devicesの有効な個数
inline int num_devices;

void WriteAddress(uint32_t address);
void WriteData(uint32_t value);
uint32_t ReadData(void);
uint16_t ReadVenderId(uint8_t bus, uint8_t device, uint8_t function);
uint16_t ReadDeviceId(uint8_t bus, uint8_t device, uint8_t function);
uint8_t ReadHeaderType(uint8_t bus, uint8_t device, uint8_t function);
uint32_t ReadClassCode(uint8_t bus, uint8_t device, uint8_t function);
uint32_t ReadBusNumbers(uint8_t bus, uint8_t device, uint8_t function);

//単機能デバイスかどうか判定する関数
bool IsSingleFunctionDevice(uint8_t header_type);



Error ScanAllBus();

} // namespace pci