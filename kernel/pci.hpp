#include "error.hpp"

namespace {

}
namespace pci{

// CONFIG_ADDRESSレジスタのIOポートアドレス
const uint16_t kConfigAddress = 0x0cf8;
// CONFIG_DATAレジスタのIOポートアドレス
const uint16_t kConfigData = 0x0cfc;

// PCIデバイスのクラスコード
struct ClassCode{
    uint8_t base, sub, interface;

    bool Match(uint8_t b){ return b == base;}
    bool Match(uint8_t b, uint8_t s){ return Match(b) && s == sub;}
    bool Match(uint8_t b, uint8_t s, uint8_t i){
        return Match(b, s) && i == interface;
    }
};

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
    ClassCode class_code;
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
ClassCode ReadClassCode(uint8_t bus, uint8_t device, uint8_t function);
uint32_t ReadBusNumbers(uint8_t bus, uint8_t device, uint8_t function);

inline uint16_t ReadVenderId(const Device& dev){
    return ReadVenderId(dev.bus, dev.device, dev.function);
}

 /** @brief 指定された PCI デバイスの 32 ビットレジスタを読み取る */
  uint32_t ReadConfReg(const Device& dev, uint8_t reg_addr);

  void WriteConfReg(const Device& dev, uint8_t reg_addr, uint32_t value);

//単機能デバイスかどうか判定する関数
bool IsSingleFunctionDevice(uint8_t header_type);



Error ScanAllBus();

 constexpr uint8_t CalcBarAddress(unsigned int bar_index) {
    return 0x10 + 4 * bar_index;
  }

  WithError<uint64_t> ReadBar(Device& device, unsigned int bar_index);
} // namespace pci