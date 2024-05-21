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
    struct Altitude
    {
      float Alt;
      float SurfAlt;
    } __attribute__((packed));

    struct Apsides
    {
      float Periapsis;
      float Apoapsis;
    } __attribute__((packed));

    struct ApsidesTime
    {
      int Periapsis;
      int Apoapsis;
    } __attribute__((packed));

    struct Velocity
    {
      float Orbital;
      float Surface;
      float Vertical;
    } __attribute__((packed));

    struct Rotation
    {
      float Heading;
      float Pitch;
      float Roll;
      float OrbitalVelocityHeading;
      float OrbitalVelocityPitch;
      float SurfaceVelocityHeading;
      float SurfaceVelocityPitch;
    } __attribute__((packed));

    struct OrbitInfo
    {
      float Eccentricity;
      float SemiMajorAxis;
      float Inclination;
      float LongAscendingNode;
      float ArgPeriapsis;
      float TrueAnomaly;
      float MeanAnomaly;
      float Period;
    } __attribute__((packed));

    struct Airspeed
    {
      float IndicatedAirSpeed;
      float MachNumber;
      float GeeForce;
    } __attribute__((packed));

    struct Maneuver
    {
      float TimeToNextManeuver;
      float DeltaVNextManeuver;
      float DurationNextManeuver;
      float DeltaVTotal;
      float HeadingNextManeuver;
      float PitchNextManeuver;
    } __attribute__((packed));

    struct SASInfo
    {
      AutoPilotModeEnum CurrentSASMode;
      AutoPilotModeFlags SASModeAvailability;
    } __attribute__((packed));

    struct RotationCmd
    {
      short Pitch;
      short Roll;
      short Yaw;
      byte Mask;
    } __attribute__((packed));

    struct TranslationCmd
    {
      short X;
      short Y;
      short Z;
      byte Mask;
    } __attribute__((packed));

    struct WheelCmd
    {
      short Steer;
      short Throttle;
      byte Mask;
    } __attribute__((packed));

    struct ThrottleCmd
    {
      short Value;
    } __attribute__((packed));

    struct ActionGroups
    {
      ActionGroupFlags Flags;
    } __attribute__((packed));

    struct DeltaV
    {
      float StageDeltaV;
      float TotalDeltaV;
    } __attribute__((packed));

    struct DeltaVEnv
    {
      float StageDeltaVASL;
      float TotalDeltaVASL;
      float StageDeltaVVac;
      float TotalDeltaVVac;
    } __attribute__((packed));

    struct BurnTime
    {
      float StageBurnTime;
      float TotalBurnTime;
    } __attribute__((packed));

    struct CustomActionGroups
    {
      byte Status[32];
    } __attribute__((packed));

    struct TempLimit
    {
      byte TempLimitPercentage;
      byte SkinTempLimitPercentage;
    } __attribute__((packed));
  };

  class Outgoing
  {
  public:
    struct CustomActionGroupEnable
    {
      byte GroupIds[32];
    } __attribute__((packed));

    struct CustomActionGroupDisable
    {
      byte GroupIds[32];
    } __attribute__((packed));

    struct CustomActionGroupToggle
    {
      byte GroupIds[32];
    } __attribute__((packed));

    struct ActionGroupActivate
    {
      ActionGroupFlags Flags;
    } __attribute__((packed));

    struct ActionGroupDeactivate
    {
      ActionGroupFlags Flags;
    } __attribute__((packed));

    struct ActionGroupToggle
    {
      ActionGroupFlags Flags;
    } __attribute__((packed));

    struct Rotation
    {
      short Pitch;
      short Roll;
      short Yaw;
      byte Mask;
    } __attribute__((packed));

    struct Translation
    {
      short X;
      short Y;
      short Z;
      byte Mask;
    } __attribute__((packed));

    struct WheelControl
    {
      short Steer;
      short Throttle;
      byte Mask;
    } __attribute__((packed));

    struct Throttle
    {
      short Value;
    } __attribute__((packed));

    struct AutopilotMode
    {
      AutoPilotModeEnum Value;
    } __attribute__((packed));

    struct CustomAxix
    {
      short Custom1;
      short Custom2;
      short Custom3;
      short Custom4;
      byte Mask;
    } __attribute__((packed));
  };
};

class Camera
{
public:
  class Outgoing
  {
  public:
    struct CameraMode
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
      } __attribute__((packed));

      ValueEnum Value;
    } __attribute__((packed));

    struct CameraRotation
    {
      short Pitch;
      short Roll;
      short Yaw;
      short Zoom;
      byte Mask;
    } __attribute__((packed));

    struct CameraTranslation
    {
      short X;
      short Y;
      short Z;
      byte Mask;
    } __attribute__((packed));
  };
};

class Environment
{
public:
  class Incoming
  {
  public:
    struct TargetInfo
    {
      float Distance;
      float Velocity;
      float Heading;
      float Pitch;
      float VelocityHeading;
      float VelocityPitch;
    } __attribute__((packed));

    struct SoIName
    {
      FixedString Value;
    } __attribute__((packed));

    struct SceneChange
    {
      enum struct SceneChangeTypeEnum
      {
        Flight = 0x0,
        NotFlight = 0x1
      } __attribute__((packed));

      SceneChangeTypeEnum Type;
    } __attribute__((packed));

    struct FlightStatus
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
      } __attribute__((packed));

      StatusFlags Status;
      byte VesselSituation; // See Vessel.Situations for possible values
      byte CurrentTWIndex;
      byte CrewCapacity;
      byte CrewCount;
      byte CommNetSignalStrenghPercentage;
      byte CurrentStage;
      byte VesselType;
    } __attribute__((packed));

    struct AtmoCondition
    {
      enum struct AtmoCharacteristicsFlags : byte
      {
        None = 0,
        HasAtmosphere = 1,
        HasOxygen = 2,
        IsVesselInAtmosphere = 4
      } __attribute__((packed));

      AtmoCharacteristicsFlags AtmoCharacteristics;
      float AirDensity;
      float Temperature;
      float Pressure;
    } __attribute__((packed));

    struct VesselName
    {
      FixedString Value;
    } __attribute__((packed));

    struct VesselChange
    {
      enum struct TypeEnum : byte
      {
        Switching = 1,
        Docking = 2,
        Undocking = 3
      } __attribute__((packed));

      TypeEnum Type;
    } __attribute__((packed));
  };
};

class Input
{
  public:
  class Outgoing
  {
    public:
    struct KeyboardEmulator
    {
      enum struct ModifierFlags : byte
      {
        SHIFT_MOD = 1,
        CTRL_MOD = 2,
        ALT_MOD = 4,
        KEY_DOWN_MOD = 8,
        KEY_UP_MOD = 16
      } __attribute__((packed));

      ModifierFlags Modifier;
      short Key;
    } __attribute__((packed));
  };
};

class NavBall
{
public:
  class Outgoing
  {
  public:
      struct NavballMode
    {
      // TODO: Check if any data is actually transmitted with this message
      // If there is, it seems unnecessary
    } __attribute__((packed));
  };
};

class Resource
{
public:
  class Incoming
  {
  public:
    struct LiquidFuel
    {
      float Max;
      float Available;
    } __attribute__((packed));

    struct LiquidFuelStage
    {
      float Max;
      float Available;
    } __attribute__((packed));

    struct Methane
    {
      float Max;
      float Available;
    } __attribute__((packed));

    struct MethaneStage
    {
      float Max;
      float Available;
    } __attribute__((packed));

    struct Oxidizer
    {
      float Max;
      float Available;
    } __attribute__((packed));

    struct OxidizerStage
    {
      float Max;
      float Available;
    } __attribute__((packed));

    struct SolidFuel
    {
      float Max;
      float Available;
    } __attribute__((packed));

    struct SolidFuelStage
    {
      float Max;
      float Available;
    } __attribute__((packed));

    struct XenonGas
    {
      float Max;
      float Available;
    } __attribute__((packed));

    struct XenonGasStage
    {
      float Max;
      float Available;
    } __attribute__((packed));

    struct MonoPropellant
    {
      float Max;
      float Available;
    } __attribute__((packed));

    struct EvaPropellant
    {
      float Max;
      float Available;
    } __attribute__((packed));

    struct ElectricCharge
    {
      float Max;
      float Available;
    } __attribute__((packed));

    struct Ore
    {
      float Max;
      float Available;
    } __attribute__((packed));

    struct Ablator
    {
      float Max;
      float Available;
    } __attribute__((packed));

    struct AblatorStage
    {
      float Max;
      float Available;
    } __attribute__((packed));

    struct CustomResourceOne
    {
      float CurrentResource1;
      float MaxResource1;
      float CurrentResource2;
      float MaxResource2;
      float CurrentResource3;
      float MaxResource3;
      float CurrentResource4;
      float MaxResource4;
    } __attribute__((packed));

    struct CustomResourceTwo
    {
      float CurrentResource1;
      float MaxResource1;
      float CurrentResource2;
      float MaxResource2;
      float CurrentResource3;
      float MaxResource3;
      float CurrentResource4;
      float MaxResource4;
    } __attribute__((packed));
  };
};

class Warp
{
  public:
  class Outgoing
  {
  public:
    struct WarpChange
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
      } __attribute__((packed));

      RateEnum Rate;
    } __attribute__((packed));

    struct TimewarpTo
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
      } __attribute__((packed));

      InstanceEnum Instant;
      float Delay; // negative for warping before the instant
    } __attribute__((packed));
  };
};

#endif