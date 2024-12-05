#include <memory>

#include <EIPScanner/cip/Types.h>
#include <EIPScanner/vendor/teknic/clearlink/MotorConfigAssemblyObject.h>
#include <EIPScanner/vendor/teknic/clearlink/MotorInputAssemblyObject.h>
#include <EIPScanner/vendor/teknic/clearlink/MotorOutputAssemblyObject.h>

using eipScanner::vendor::teknic::clearlink::MotorConfigAssemblyObject;
using eipScanner::vendor::teknic::clearlink::MotorInputAssemblyObject;
using eipScanner::vendor::teknic::clearlink::MotorOutputAssemblyObject;

using eipScanner::cip::CipDint;
using eipScanner::cip::CipUdint;

// Taken from spec sheet:
// https://www.teknic.com/files/downloads/clearlink_ethernet-ip_object_reference.pdf#page=46
const eipScanner::cip::CipUdint MAX_STEPS_PER_SECOND = 500000;
const eipScanner::cip::CipUdint MAX_ACCELERATION_STEPS_PER_SECOND_SQUARED =
    500000;

enum class MoveInstructionState { COMPLETED, IN_PROGRESS, FAULTED };

struct MotorIO {
  std::shared_ptr<MotorConfigAssemblyObject> configPtr;
  std::shared_ptr<MotorInputAssemblyObject> inputPtr;
  std::shared_ptr<MotorOutputAssemblyObject> outputPtr;

  // TEMP: Until this is integrated into the SDMotor* objects
  double stepsPerUnit;
  double maxSetPositionVelocity;
  double maxSetPositionAcceleration;
  double maxSetVelocityAcceleration;
};

// TODO: Move InputShutdowns to the SDMotorInputObject class
enum InputShutdowns {
  MotionCanceled_CommandWhileShutdown = 0,
  MotionCanceled_PosLimit = 1,
  MotionCanceled_NegLimit = 2,
  MotionCanceled_SensorEStop = 3,
  MotionCanceled_SoftwareEStop = 4,
  MotionCanceled_MotorDisabled = 5,
  MotionCanceled_SoftLimitExceeded = 6,
  MotionCanceled_FollowerAxisFault = 7,
  MotionCanceled_CommandWhileFollowing = 8,
  MotionCanceled_HomingNotReady = 9,
  MotorFaulted = 10,
  FollowingOverspeed = 11,
  NUM_STATES = 12,
  // 13 - 31 are reserved
};

void initializeMotorLimitSensors(
    std::shared_ptr<MotorConfigAssemblyObject> motorConfigObjectPtr,
    double brakeControlPinId, double positiveLimitPinId,
    double negativeLimitPinId, double homingSensorPinId,
    CipDint positiveSoftLimit, CipDint negativeSoftLimit)

{
  motorConfigObjectPtr->setBrakeOutputConnector(brakeControlPinId);
  motorConfigObjectPtr->setPositiveLimitConnector(positiveLimitPinId);
  motorConfigObjectPtr->setNegativeLimitConnector(negativeLimitPinId);
  motorConfigObjectPtr->setHomeSensorConnector(homingSensorPinId);

  motorConfigObjectPtr->setSoftLimitPosition1(positiveSoftLimit);
  motorConfigObjectPtr->setSoftLimitPosition2(negativeSoftLimit);

  motorConfigObjectPtr->setConfigFlag(
      SDMotorConfigObject::ConfigFlag::HomingEnable, true);
  motorConfigObjectPtr->setConfigFlag(
      SDMotorConfigObject::ConfigFlag::HLFBInversion, true);
  motorConfigObjectPtr->setConfigFlag(
      SDMotorConfigObject::ConfigFlag::SoftwareLimitEnable, false);
}

/*
void initializeMovementLimits(std::shared_ptr<SDMotorOutputObject>
motorOutputObjectPtr);

bool faultsClearedSuccessfully(std::shared_ptr<SDMotorInputObject>
motorInputObjectPtr, std::shared_ptr<SDMotorOutputObject> motorOutputObjectPtr);

bool faultsClearedSuccessfully(std::shared_ptr<SDMotorInputObject>
motorInputObjectPtr, std::shared_ptr<SDMotorOutputObject> motorOutputObjectPtr);

void loadMotorMoveCommand(std::shared_ptr<SDMotorOutputObject>
motorOutputObjectPtr, SDMotorOutputObject::OutputFlag loadMoveFlag, CipUdint
maxVelocitySteps, CipUdint maxAccelerationSteps);

void setMotorPositionMoveCommand(std::shared_ptr<SDMotorOutputObject>
motorOutputObjectPtr, int positionSetPoint, CipUdint maxVelocitySteps, CipUdint
maxAccelerationSteps, bool absoluteMove);

void unsetMotorPositionMoveCommand(std::shared_ptr<SDMotorInputObject>
motorInputObjectPtr, std::shared_ptr<SDMotorOutputObject> motorOutputObjectPtr);

MoveInstructionState
moveToMotorPositionNonBlocking(std::shared_ptr<SDMotorInputObject>
motorInputObjectPtr, std::shared_ptr<SDMotorOutputObject> motorOutputObjectPtr,
                                                    int positionSetPoint,
                                                    CipUdint maxVelocitySteps,
                                                    CipUdint
maxAccelerationSteps, bool absoluteMove = false);

void setMotorVelocityMoveCommand(std::shared_ptr<SDMotorOutputObject>
motorOutputObjectptr, int velocitySetPoint, CipUdint maxAccelerationSteps);

void unsetMotorVelocityMoveCommand(std::shared_ptr<SDMotorInputObject>
motorInputObjectPtr, std::shared_ptr<SDMotorOutputObject> motorOutputObjectPtr);

MoveInstructionState
moveToMotorVelocityNonBlocking(std::shared_ptr<SDMotorInputObject>
motorInputObjectPtr, std::shared_ptr<SDMotorOutputObject> motorOutputObjectPtr,
                                                    int velocitySetPoint,
                                                    CipUdint
maxAccelerationSteps);

bool homeMotor(std::shared_ptr<SDMotorInputObject> motorInputObjectPtr,
               std::shared_ptr<SDMotorOutputObject> motorOutputObjectPtr);

} // namespace motorIO

} // namespace motorController

*/
