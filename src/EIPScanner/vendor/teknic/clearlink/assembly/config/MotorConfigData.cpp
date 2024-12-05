//
// Created by Jan Ritzenhoff on 12/5/2024
//
#include "EIPScanner/vendor/teknic/clearlink/assembly/config/MotorConfigData.h"

namespace eipScanner {
namespace vendor {
namespace teknic {
namespace clearlink {
namespace assembly {
namespace config {

MotorConfigData::MotorConfigData()
    : BaseAssemblyData(), _configRegister(), _followDivisor(),
      _followMultiplier(), _maxDeceleration(), _softLimitPosition1(),
      _softLimitPosition2(), _positiveLimitConnector(),
      _negativeLimitConnector(), _homeSensorConnector(),
      _brakeOutputConnector(), _stopSensorConnector(),
      _triggerPositionCaptureConnector(), _followAxis(),
      _reservedPadding(PADDING_BYTES_SIZE) {}

std::vector<BaseAssemblyData::DataFieldReference>
MotorConfigData::_getDataFieldReferences() {
  return {std::ref(_configRegister),
          std::ref(_followDivisor),
          std::ref(_followMultiplier),
          std::ref(_maxDeceleration),
          std::ref(_softLimitPosition1),
          std::ref(_softLimitPosition2),
          std::ref(_positiveLimitConnector),
          std::ref(_negativeLimitConnector),
          std::ref(_homeSensorConnector),
          std::ref(_brakeOutputConnector),
          std::ref(_stopSensorConnector),
          std::ref(_triggerPositionCaptureConnector),
          std::ref(_followAxis),
          std::ref(_reservedPadding)};
}
} // namespace config
} // namespace assembly
} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner
