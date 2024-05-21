#ifndef KerbalSimpitMessageTypeIds_h
#define KerbalSimpitMessageTypeIds_h

class MessageTypeIds
{
public:
    class Incoming
    {
    public:
        //#region Propulsion Resources
        static const byte LiquidFuel = 10;
        static const byte LiquidFuelStage = 11;
        static const byte Methane = 10;
        static const byte MethaneStage = 11;
        static const byte Oxidizer = 12;
        static const byte OxidizerStage = 13;
        static const byte SolidFuel = 14;
        static const byte SolidFuelStage = 15;
        static const byte XenonGas = 28;
        static const byte XenonGasStage = 29;
        static const byte MonoPropellant = 16;
        static const byte EvaPropellant = 18;

        //Propulsion Resources on KSP2
        static const byte IntakeAir = 52;
        //static const byte TestRocks = xx; //Available in KSP2 but seems to be unused
        static const byte Hydrogen = 53;
        static const byte HydrogenStage = 54;
        //static const byte Methalox = xx; //Available in KSP2 but seems to be unused
        //static const byte MethaloxStage = xx; //Available in KSP2 but seems to be unused
        //static const byte MethaneAir = xx; //Available in KSP2 but seems to be unused
        //static const byte MethaneAirStage = xx; //Available in KSP2 but seems to be unused
        static const byte Uranium = 55;
        //static const byte XenonEC = xx; //Available in KSP2 but seems to be unused
        //static const byte XenonECStage = xx; //Available in KSP2 but seems to be unused
        //#endregion

        //#region Vessel Resources
        static const byte ElectricCharge = 17;
        static const byte Ore = 19;
        static const byte Ablator = 20;
        static const byte AblatorStage = 21;
        static const byte TACLSResource = 30;
        static const byte TACLSWaste = 31;
        static const byte CustomResource1 = 32;
        static const byte CustomResource2 = 33;
        //#endregion

        //#region Vessel Movement/Postion
        static const byte Altitude = 8;
        static const byte Velocity = 22;
        static const byte Airspeed = 27;
        static const byte Apsides = 9;
        static const byte ApsidesTime = 24;
        static const byte ManeuverData = 34;
        static const byte SASInfo = 35;
        static const byte OrbitInfo = 36;
        static const byte Rotation = 45;
        //#endregion

        //#region Vessel Commands
        static const byte RotationCmd = 47;
        static const byte TranslationCmd = 48;
        static const byte WheelCmd = 49;
        static const byte ThrottleCmd = 50;
        //#endregion

        //#region Vessel Details
        static const byte ActionGroups = 37;
        static const byte DeltaV = 38;
        static const byte DeltaVEnv = 39;
        static const byte BurnTime = 40;
        static const byte CustomActionGroups = 41;
        static const byte TempLimit = 42;
        static const byte AdvancedActionGroups = 56; // Appears to be unused in KerbalSimpitRevamped
        static const byte AdvancedCustomActionGroups = 57;  // Appears to be unused in KerbalSimpitRevamped
        //#endregion

        //#region External Environment
        static const byte TargetInfo = 25;
        static const byte SoIName = 26;
        static const byte SceneChange = 3;
        static const byte FlightStatus = 43;
        static const byte AtmoCondition = 44;
        static const byte VesselName = 46;
        static const byte VesselChange = 51;
        //#endregion
    };

    class Outgoing
    {
    public:
        static const byte CustomActionGroupEnable = 10;
        static const byte CustomActionGroupDisable = 11;
        static const byte CustomActionGroupToggle = 12;
        static const byte ActionGroupActivate = 13;
        static const byte ActionGroupDeactivate = 14;
        static const byte ActionGroupToggle = 15;
        // static const byte SetSingleActionGroup = 58;
        // static const byte SetSingleCAG = 59;
        static const byte Rotation = 16;
        static const byte Translation = 17;
        static const byte WheelControl = 18;
        static const byte Throttle = 19;
        static const byte AutopilotMode = 20;
        static const byte CameraMode = 21;
        static const byte CameraRotation = 22;
        static const byte CameraTranslation = 23;
        static const byte WarpChange = 24;
        static const byte TimewarpTo = 30;
        static const byte KeyboardEmulator = 26;
        static const byte VesselCustomAxis = 27;
        static const byte NavballMode = 28;
    };
};

#endif
