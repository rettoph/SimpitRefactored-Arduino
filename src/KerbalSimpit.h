#ifndef KerbalSimpit_h
#define KerbalSimpit_h

#include "SimpitBuilder.h"
#include "KerbalSimpitMessageTypeIds.h"
#include "KerbalSimpitMessageTypes.h"
#include "SimpitMacros.h"

// Propulsion Resources
SIMPIT_DECLARE_INCOMING_TYPE(Resource::Incoming::LiquidFuel, MessageTypeIds::Incoming::LiquidFuel);
SIMPIT_DECLARE_INCOMING_TYPE(Resource::Incoming::LiquidFuelStage, MessageTypeIds::Incoming::LiquidFuelStage);
SIMPIT_DECLARE_INCOMING_TYPE(Resource::Incoming::Oxidizer, MessageTypeIds::Incoming::Oxidizer);
SIMPIT_DECLARE_INCOMING_TYPE(Resource::Incoming::OxidizerStage, MessageTypeIds::Incoming::OxidizerStage);
SIMPIT_DECLARE_INCOMING_TYPE(Resource::Incoming::SolidFuel, MessageTypeIds::Incoming::SolidFuel);
SIMPIT_DECLARE_INCOMING_TYPE(Resource::Incoming::SolidFuelStage, MessageTypeIds::Incoming::SolidFuelStage);
SIMPIT_DECLARE_INCOMING_TYPE(Resource::Incoming::XenonGas, MessageTypeIds::Incoming::XenonGas);
SIMPIT_DECLARE_INCOMING_TYPE(Resource::Incoming::XenonGasStage, MessageTypeIds::Incoming::XenonGasStage);
SIMPIT_DECLARE_INCOMING_TYPE(Resource::Incoming::MonoPropellant, MessageTypeIds::Incoming::MonoPropellant);
SIMPIT_DECLARE_INCOMING_TYPE(Resource::Incoming::EvaPropellant, MessageTypeIds::Incoming::EvaPropellant);

// Vessel Resources
SIMPIT_DECLARE_INCOMING_TYPE(Resource::Incoming::ElectricCharge, MessageTypeIds::Incoming::ElectricCharge);
SIMPIT_DECLARE_INCOMING_TYPE(Resource::Incoming::Ore, MessageTypeIds::Incoming::Ore);
SIMPIT_DECLARE_INCOMING_TYPE(Resource::Incoming::Ablator, MessageTypeIds::Incoming::Ablator);
SIMPIT_DECLARE_INCOMING_TYPE(Resource::Incoming::AblatorStage, MessageTypeIds::Incoming::AblatorStage);
SIMPIT_DECLARE_INCOMING_TYPE(Resource::Incoming::CustomResourceOne, MessageTypeIds::Incoming::CustomResource1);
SIMPIT_DECLARE_INCOMING_TYPE(Resource::Incoming::CustomResourceTwo, MessageTypeIds::Incoming::CustomResource2);

// Vessel Movement/Postion
SIMPIT_DECLARE_INCOMING_TYPE(Vessel::Incoming::Altitude, MessageTypeIds::Incoming::Altitude);
SIMPIT_DECLARE_INCOMING_TYPE(Vessel::Incoming::Velocity, MessageTypeIds::Incoming::Velocity);
SIMPIT_DECLARE_INCOMING_TYPE(Vessel::Incoming::Airspeed, MessageTypeIds::Incoming::Airspeed);
SIMPIT_DECLARE_INCOMING_TYPE(Vessel::Incoming::Apsides, MessageTypeIds::Incoming::Apsides);
SIMPIT_DECLARE_INCOMING_TYPE(Vessel::Incoming::ApsidesTime, MessageTypeIds::Incoming::ApsidesTime);
SIMPIT_DECLARE_INCOMING_TYPE(Vessel::Incoming::Maneuver, MessageTypeIds::Incoming::ManeuverData);
SIMPIT_DECLARE_INCOMING_TYPE(Vessel::Incoming::SASInfo, MessageTypeIds::Incoming::SASInfo);
SIMPIT_DECLARE_INCOMING_TYPE(Vessel::Incoming::OrbitInfo, MessageTypeIds::Incoming::OrbitInfo);
SIMPIT_DECLARE_INCOMING_TYPE(Vessel::Incoming::Rotation, MessageTypeIds::Incoming::Rotation);

// Vessel commands
SIMPIT_DECLARE_INCOMING_TYPE(Vessel::Incoming::RotationCmd, MessageTypeIds::Incoming::RotationCmd);
SIMPIT_DECLARE_INCOMING_TYPE(Vessel::Incoming::TranslationCmd, MessageTypeIds::Incoming::TranslationCmd);
SIMPIT_DECLARE_INCOMING_TYPE(Vessel::Incoming::WheelCmd, MessageTypeIds::Incoming::WheelCmd);
SIMPIT_DECLARE_INCOMING_TYPE(Vessel::Incoming::ThrottleCmd, MessageTypeIds::Incoming::ThrottleCmd);

// Vessel Details
SIMPIT_DECLARE_INCOMING_TYPE(Vessel::Incoming::ActionGroups, MessageTypeIds::Incoming::ActionGroups);
SIMPIT_DECLARE_INCOMING_TYPE(Vessel::Incoming::DeltaV, MessageTypeIds::Incoming::DeltaV);
SIMPIT_DECLARE_INCOMING_TYPE(Vessel::Incoming::DeltaVEnv, MessageTypeIds::Incoming::DeltaVEnv);
SIMPIT_DECLARE_INCOMING_TYPE(Vessel::Incoming::BurnTime, MessageTypeIds::Incoming::BurnTime);
SIMPIT_DECLARE_INCOMING_TYPE(Vessel::Incoming::CustomActionGroups, MessageTypeIds::Incoming::CustomActionGroups);
SIMPIT_DECLARE_INCOMING_TYPE(Vessel::Incoming::TempLimit, MessageTypeIds::Incoming::TempLimit);

// External Environment
SIMPIT_DECLARE_INCOMING_TYPE(Environment::Incoming::TargetInfo, MessageTypeIds::Incoming::TargetInfo);
SIMPIT_DECLARE_INCOMING_TYPE(Environment::Incoming::SoIName, MessageTypeIds::Incoming::SoIName);
SIMPIT_DECLARE_INCOMING_TYPE(Environment::Incoming::SceneChange, MessageTypeIds::Incoming::SceneChange);
SIMPIT_DECLARE_INCOMING_TYPE(Environment::Incoming::FlightStatus, MessageTypeIds::Incoming::FlightStatus);
SIMPIT_DECLARE_INCOMING_TYPE(Environment::Incoming::AtmoCondition, MessageTypeIds::Incoming::AtmoCondition);
SIMPIT_DECLARE_INCOMING_TYPE(Environment::Incoming::VesselName, MessageTypeIds::Incoming::VesselName);
SIMPIT_DECLARE_INCOMING_TYPE(Environment::Incoming::VesselChange, MessageTypeIds::Incoming::VesselChange);

// Outgoing
SIMPIT_DECLARE_OUTGOING_TYPE(Vessel::Outgoing::CustomActionGroupEnable, MessageTypeIds::Outgoing::CustomActionGroupEnable);
SIMPIT_DECLARE_OUTGOING_TYPE(Vessel::Outgoing::CustomActionGroupDisable, MessageTypeIds::Outgoing::CustomActionGroupDisable);
SIMPIT_DECLARE_OUTGOING_TYPE(Vessel::Outgoing::CustomActionGroupToggle, MessageTypeIds::Outgoing::CustomActionGroupToggle);
SIMPIT_DECLARE_OUTGOING_TYPE(Vessel::Outgoing::ActionGroupActivate, MessageTypeIds::Outgoing::ActionGroupActivate);
SIMPIT_DECLARE_OUTGOING_TYPE(Vessel::Outgoing::ActionGroupDeactivate, MessageTypeIds::Outgoing::ActionGroupDeactivate);
SIMPIT_DECLARE_OUTGOING_TYPE(Vessel::Outgoing::ActionGroupToggle, MessageTypeIds::Outgoing::ActionGroupToggle);
SIMPIT_DECLARE_OUTGOING_TYPE(Vessel::Outgoing::Rotation, MessageTypeIds::Outgoing::Rotation);
SIMPIT_DECLARE_OUTGOING_TYPE(Vessel::Outgoing::Translation, MessageTypeIds::Outgoing::Translation);
SIMPIT_DECLARE_OUTGOING_TYPE(Vessel::Outgoing::WheelControl, MessageTypeIds::Outgoing::WheelControl);
SIMPIT_DECLARE_OUTGOING_TYPE(Vessel::Outgoing::Throttle, MessageTypeIds::Outgoing::Throttle);
SIMPIT_DECLARE_OUTGOING_TYPE(Vessel::Outgoing::AutopilotMode, MessageTypeIds::Outgoing::AutopilotMode);

SIMPIT_DECLARE_OUTGOING_TYPE(Camera::Outgoing::CameraMode, MessageTypeIds::Outgoing::CameraMode);
SIMPIT_DECLARE_OUTGOING_TYPE(Camera::Outgoing::CameraRotation, MessageTypeIds::Outgoing::CameraRotation);
SIMPIT_DECLARE_OUTGOING_TYPE(Camera::Outgoing::CameraTranslation, MessageTypeIds::Outgoing::CameraTranslation);

SIMPIT_DECLARE_OUTGOING_TYPE(Warp::Outgoing::WarpChange, MessageTypeIds::Outgoing::WarpChange);
SIMPIT_DECLARE_OUTGOING_TYPE(Warp::Outgoing::TimewarpTo, MessageTypeIds::Outgoing::TimewarpTo);

SIMPIT_DECLARE_OUTGOING_TYPE(NavBall::Outgoing::NavballMode, MessageTypeIds::Outgoing::NavballMode);

SIMPIT_DECLARE_OUTGOING_TYPE(Input::Outgoing::KeyboardEmulator, MessageTypeIds::Outgoing::KeyboardEmulator);

#endif