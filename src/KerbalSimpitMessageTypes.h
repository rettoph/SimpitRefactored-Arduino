#ifndef KerbalSimpitMessageTypes_h
#define KerbalSimpitMessageTypes_h

#include "FixedString.h"

enum struct ActionGroupFlags : byte
{
  None = 0,
  Stage = 1,
  Gear = 2,
  Light = 4,
  RCS = 8,
  SAS = 16,
  Brakes = 32,
  Abort = 64
};

enum struct AutoPilotModeEnum : byte
{
  StabilityAssist = 0,
  Prograde = 1,
  Retrograde = 2,
  Normal = 3,
  Antinormal = 4,
  RadialIn = 5,
  RadialOut = 6,
  Target = 7,
  AntiTarget = 8,
  Maneuver = 9,
  Disabled = 255
};

enum struct AutoPilotModeFlags : uint16_t
{
  None = 0,
  StabilityAssist = 1,
  Prograde = 2,
  Retrograde = 4,
  Normal = 8,
  Antinormal = 16,
  RadialIn = 32,
  RadialOut = 64,
  Target = 128,
  AntiTarget = 256,
  Maneuver = 512
};

class Vessel
{
public:
  class Incoming
  {
  public:
    struct __attribute__((packed)) Altitude
    {
      float Alt;
      float SurfAlt;
    };

    struct __attribute__((packed)) Apsides
    {
      float Periapsis;
      float Apoapsis;
    };

    struct __attribute__((packed)) ApsidesTime
    {
      int32_t Periapsis;
      int32_t Apoapsis;
    };

    struct __attribute__((packed)) Velocity
    {
      float Orbital;
      float Surface;
      float Vertical;
    };

    struct __attribute__((packed)) Rotation
    {
      float Heading;
      float Pitch;
      float Roll;
      float OrbitalVelocityHeading;
      float OrbitalVelocityPitch;
      float SurfaceVelocityHeading;
      float SurfaceVelocityPitch;
    };

    struct __attribute__((packed)) OrbitInfo
    {
      float Eccentricity;
      float SemiMajorAxis;
      float Inclination;
      float LongAscendingNode;
      float ArgPeriapsis;
      float TrueAnomaly;
      float MeanAnomaly;
      float Period;
    };

    struct __attribute__((packed)) Airspeed
    {
      float IndicatedAirSpeed;
      float MachNumber;
      float GeeForce;
    };

    struct __attribute__((packed)) Maneuver
    {
      float TimeToNextManeuver;
      float DeltaVNextManeuver;
      float DurationNextManeuver;
      float DeltaVTotal;
      float HeadingNextManeuver;
      float PitchNextManeuver;
    };

    struct __attribute__((packed)) SASInfo
    {
      AutoPilotModeEnum CurrentSASMode;
      AutoPilotModeFlags SASModeAvailability;
    };

    struct __attribute__((packed)) RotationCmd
    {
      short Pitch;
      short Roll;
      short Yaw;
      byte Mask;
    };

    struct __attribute__((packed)) TranslationCmd
    {
      short X;
      short Y;
      short Z;
      byte Mask;
    };

    struct __attribute__((packed)) WheelCmd
    {
      short Steer;
      short Throttle;
      byte Mask;
    };

    struct __attribute__((packed)) ThrottleCmd
    {
      short Value;
    };

    struct __attribute__((packed)) ActionGroups
    {
      ActionGroupFlags Flags;
    };

    struct __attribute__((packed)) DeltaV
    {
      float StageDeltaV;
      float TotalDeltaV;
    };

    struct __attribute__((packed)) DeltaVEnv
    {
      float StageDeltaVASL;
      float TotalDeltaVASL;
      float StageDeltaVVac;
      float TotalDeltaVVac;
    };

    struct __attribute__((packed)) BurnTime
    {
      float StageBurnTime;
      float TotalBurnTime;
    };

    struct __attribute__((packed)) CustomActionGroups
    {
      byte Status[32];
    };

    struct __attribute__((packed)) TempLimit
    {
      byte TempLimitPercentage;
      byte SkinTempLimitPercentage;
    };
  };

  class Outgoing
  {
  public:
    struct __attribute__((packed)) CustomActionGroupEnable
    {
      byte GroupIds[32];
    };

    struct __attribute__((packed)) CustomActionGroupDisable
    {
      byte GroupIds[32];
    };

    struct __attribute__((packed)) CustomActionGroupToggle
    {
      byte GroupIds[32];
    };

    struct __attribute__((packed)) ActionGroupActivate
    {
      ActionGroupFlags Flags;
    };

    struct __attribute__((packed)) ActionGroupDeactivate
    {
      ActionGroupFlags Flags;
    };

    struct __attribute__((packed)) ActionGroupToggle
    {
      ActionGroupFlags Flags;
    };

    struct __attribute__((packed)) Rotation
    {
      short Pitch;
      short Roll;
      short Yaw;
      byte Mask;
    };

    struct __attribute__((packed)) Translation
    {
      short X;
      short Y;
      short Z;
      byte Mask;
    };

    struct __attribute__((packed)) WheelControl
    {
      short Steer;
      short Throttle;
      byte Mask;
    };

    struct __attribute__((packed)) Throttle
    {
      short Value;
    };

    struct __attribute__((packed)) AutopilotMode
    {
      AutoPilotModeEnum Value;
    };

    struct __attribute__((packed)) CustomAxix
    {
      short Custom1;
      short Custom2;
      short Custom3;
      short Custom4;
      byte Mask;
    };
  };
};

class Camera
{
public:
  class Outgoing
  {
  public:
    struct __attribute__((packed)) CameraMode
    {
      enum struct ValueEnum : byte
      {
        FlightMode = 1,
        Auto = 2,
        Free = 3,
        Orbital = 4,
        Chase = 5,
        Locked = 6,
        IVAMode = 10,
        PlanetaryMode = 20,
        NextCamera = 50,
        PreviousCamera = 51,
        NextCameraModeState = 52,
        PreviousCameraModeState = 53
      };

      ValueEnum Value;
    };

    struct __attribute__((packed)) CameraRotation
    {
      short Pitch;
      short Roll;
      short Yaw;
      short Zoom;
      byte Mask;
    };

    struct __attribute__((packed)) CameraTranslation
    {
      short X;
      short Y;
      short Z;
      byte Mask;
    };
  };
};

class Environment
{
public:
  class Incoming
  {
  public:
    struct __attribute__((packed)) TargetInfo
    {
      float Distance;
      float Velocity;
      float Heading;
      float Pitch;
      float VelocityHeading;
      float VelocityPitch;
    };

    struct __attribute__((packed)) SoIName
    {
      FixedString Value;
    };

    struct __attribute__((packed)) SceneChange
    {
      enum struct SceneChangeTypeEnum
      {
        Flight = 0x0,
        NotFlight = 0x1
      };

      SceneChangeTypeEnum Type;
    };

    struct __attribute__((packed)) FlightStatus
    {
      enum struct StatusFlags : byte
      {
        IsInFlight = 1,
        IsEva = 2,
        IsRecoverable = 4,
        IsInAtmoTW = 8,
        ComnetControlLevel0 = 16,
        ComnetControlLevel1 = 32,
        HasTargetSet = 64
      };

      StatusFlags Status;
      byte VesselSituation; // See Vessel.Situations for possible values
      byte CurrentTWIndex;
      byte CrewCapacity;
      byte CrewCount;
      byte CommNetSignalStrenghPercentage;
      byte CurrentStage;
      byte VesselType;
    };

    struct __attribute__((packed)) AtmoCondition
    {
      enum struct AtmoCharacteristicsFlags : byte
      {
        None = 0,
        HasAtmosphere = 1,
        HasOxygen = 2,
        IsVesselInAtmosphere = 4
      };

      AtmoCharacteristicsFlags AtmoCharacteristics;
      float AirDensity;
      float Temperature;
      float Pressure;
    };

    struct __attribute__((packed)) VesselName
    {
      FixedString Value;
    };

    struct __attribute__((packed)) VesselChange
    {
      enum struct TypeEnum : byte
      {
        Switching = 1,
        Docking = 2,
        Undocking = 3
      };

      TypeEnum Type;
    };
  };
};

class Input
{
  public:
  class Outgoing
  {
    public:
    struct __attribute__((packed)) KeyboardEmulator
    {
      enum struct ModifierFlags : byte
      {
        NONE = 0,
        SHIFT_MOD = 1,
        CTRL_MOD = 2,
        ALT_MOD = 4,
        KEY_DOWN_MOD = 8,
        KEY_UP_MOD = 16
      };

      ModifierFlags Modifier;
      short Key;
    };
  };
};

class NavBall
{
public:
  class Outgoing
  {
  public:
      struct __attribute__((packed)) NavballMode
    {
      // TODO: Check if any data is actually transmitted with this message
      // If there is, it seems unnecessary
    };
  };
};

class Resource
{
public:
  class Incoming
  {
  public:
    struct __attribute__((packed)) LiquidFuel
    {
      float Max;
      float Available;
    };

    struct __attribute__((packed)) LiquidFuelStage
    {
      float Max;
      float Available;
    };

    struct __attribute__((packed)) Methane
    {
      float Max;
      float Available;
    };

    struct __attribute__((packed)) MethaneStage
    {
      float Max;
      float Available;
    };

    struct __attribute__((packed)) Oxidizer
    {
      float Max;
      float Available;
    };

    struct __attribute__((packed)) OxidizerStage
    {
      float Max;
      float Available;
    };

    struct __attribute__((packed)) SolidFuel
    {
      float Max;
      float Available;
    };

    struct __attribute__((packed)) SolidFuelStage
    {
      float Max;
      float Available;
    };

    struct __attribute__((packed)) XenonGas
    {
      float Max;
      float Available;
    };

    struct __attribute__((packed)) XenonGasStage
    {
      float Max;
      float Available;
    };

    struct __attribute__((packed)) MonoPropellant
    {
      float Max;
      float Available;
    };

    struct __attribute__((packed)) EvaPropellant
    {
      float Max;
      float Available;
    };

    struct __attribute__((packed)) ElectricCharge
    {
      float Max;
      float Available;
    };

    struct __attribute__((packed)) Ore
    {
      float Max;
      float Available;
    };

    struct __attribute__((packed)) Ablator
    {
      float Max;
      float Available;
    };

    struct __attribute__((packed)) AblatorStage
    {
      float Max;
      float Available;
    };

    struct __attribute__((packed)) CustomResourceOne
    {
      float CurrentResource1;
      float MaxResource1;
      float CurrentResource2;
      float MaxResource2;
      float CurrentResource3;
      float MaxResource3;
      float CurrentResource4;
      float MaxResource4;
    };

    struct __attribute__((packed)) CustomResourceTwo
    {
      float CurrentResource1;
      float MaxResource1;
      float CurrentResource2;
      float MaxResource2;
      float CurrentResource3;
      float MaxResource3;
      float CurrentResource4;
      float MaxResource4;
    };
  };
};

class Warp
{
  public:
  class Outgoing
  {
  public:
    struct __attribute__((packed)) WarpChange
    {
      enum struct RateEnum : byte
      {
        WarpRate1 = 0,
        WarpRate2 = 1,
        WarpRate3 = 2,
        WarpRate4 = 3,
        WarpRate5 = 4,
        WarpRate6 = 5,
        WarpRate7 = 6,
        WarpRate8 = 7,
        WarpRatePhys1 = 8,
        WarpRatePhys2 = 9,
        WarpRatePhys3 = 10,
        WarpRatePhys4 = 11,
        WarpRateUp = 12,
        WarpRateDown = 13,
        WarpCancelAutoWarp = 255,
      };

      RateEnum Rate;
    };

    struct __attribute__((packed)) TimewarpTo
    {
      enum struct InstanceEnum : byte
      {
        TimewarpToNow = 0,
        TimewarpToManeuver = 1,
        TimewarpToBurn = 2,
        TimewarpToNextSOI = 3,
        TimewarpToApoapsis = 4,
        TimewarpToPeriapsis = 5,
        TimewarpToNextMorning = 6
      };

      InstanceEnum Instant;
      float Delay; // negative for warping before the instant
    };
  };
};

#endif