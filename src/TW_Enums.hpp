#ifndef TW_ENUMS_HPP
#define TW_ENUMS_HPP

#include <iostream>
#include <unordered_map>

class TW_ENUMS
{
public:
    template <typename T>
    static T stringToEnum(const std::string& name)
    {
        try
        {
            return static_cast<T>(std::hash<std::string>{}(name));
        }
        catch (const std::exception& e)
        {
            std::cout << "Failed to convert string to enum: " << e.what() << std::endl;
        }
    }

    enum FarmAssistantTemplates
    {
        A = 6919333181322027406U,
        B = 4199750530058918380U,
        C = 12432341034569643010U
    };

    static std::string enumToFATemplate(const TW_ENUMS::FarmAssistantTemplates& name)
    {
        switch (name)
        {
            case TW_ENUMS::FarmAssistantTemplates::A:
                return "A";
                break;
            case TW_ENUMS::FarmAssistantTemplates::B:
                return "B";
                break;
            case TW_ENUMS::FarmAssistantTemplates::C:
                return "C";
                break;
            default:
                throw std::runtime_error("Could not convert enum to string.");
        }
    }

    enum EventPiority
    {
        HIGH,
        MIDDLE,
        LOW
    };

    enum BuildingNames : std::size_t
    {
        MAIN     = 11868120863286193964U,
        BARRACKS = 1324854520973102495,
        STABLE   = 1103218798469747786,
        GARAGE   = 9743424645174578744U,
        CHURCH   = 9341695719890428410U,
        CHURCH_F = 13481715487661816597U,
        SNOB     = 964809824620346523,
        SMITH    = 18158090742780098412U,
        PLACE    = 17439743817579628268U,
        STATUE   = 7091012380450742194,
        MARKET   = 11726803662808507152U,
        WOOD     = 17088299949058085397U,
        STONE    = 14560183723453781141U,  // CLAY
        IRON     = 18184064649465307815U,
        FARM     = 1690185804249701306,
        STORAGE  = 15550872211904242098U,
        HIDE     = 7990545301603493327,
        WALL     = 1357917455244345189,
        TOWER    = 3658838979580872492
    };

    static std::string enumToBuildingName(const TW_ENUMS::BuildingNames& name)
    {
        switch (name)
        {
            case TW_ENUMS::BuildingNames::MAIN:
                return "main";
            case TW_ENUMS::BuildingNames::BARRACKS:
                return "barracks";
            case TW_ENUMS::BuildingNames::STABLE:
                return "stable";
            case TW_ENUMS::BuildingNames::GARAGE:
                return "garage";
            case TW_ENUMS::BuildingNames::CHURCH:
                return "church";
            case TW_ENUMS::BuildingNames::CHURCH_F:
                return "church_f";
            case TW_ENUMS::BuildingNames::SNOB:
                return "snob";
            case TW_ENUMS::BuildingNames::SMITH:
                return "smith";
            case TW_ENUMS::BuildingNames::PLACE:
                return "place";
            case TW_ENUMS::BuildingNames::STATUE:
                return "statue";
            case TW_ENUMS::BuildingNames::MARKET:
                return "market";
            case TW_ENUMS::BuildingNames::WOOD:
                return "wood";
            case TW_ENUMS::BuildingNames::STONE:
                return "stone";
            case TW_ENUMS::BuildingNames::IRON:
                return "iron";
            case TW_ENUMS::BuildingNames::FARM:
                return "farm";
            case TW_ENUMS::BuildingNames::STORAGE:
                return "storage";
            case TW_ENUMS::BuildingNames::HIDE:
                return "hide";
            case TW_ENUMS::BuildingNames::WALL:
                return "wall";
            case TW_ENUMS::BuildingNames::TOWER:
                return "watchtower";
            default:
                throw std::runtime_error("Could not convert enum to string.");
        }
    }


    /*
     * Names for navigation elements.
     */
    enum NavigationNames : std::size_t
    {
        OVERVIEW = 0,
        MAP,
        FARM_ASSISTANT
    };

    static std::string enumToNavName(const TW_ENUMS::NavigationNames& nav)
    {
        if (nav == NavigationNames::OVERVIEW)
        {
            return "overview";
        }
        else if (nav == NavigationNames::MAP)
        {
            return "map";
        }
        else if (nav == NavigationNames::FARM_ASSISTANT)
        {
            return "farm_assistant";
        }
        else
        {
            return "";
        }
    }

    /*
     * Troop names.
     */
    enum TroopNames : std::size_t
    {
        SPEAR    = 3256959820157069409,
        SWORD    = 12017664753161582116U,
        AXE      = 8816197463898487467,
        ARCHER   = 17661862547772663856U,
        SPY      = 17257242024670138978U,
        LIGHT    = 15866780872680112420U,
        MARCHER  = 8,
        HEAVY    = 525926755921542119,
        RAM      = 13826795336199819306U,
        CATAPULT = 10341739653938705235U,
        KNIGHT   = 10142077499568241313U,
        NOBEL    = 5929400870668624538
    };

    static std::string enumToTroopName(const TW_ENUMS::TroopNames troop)
    {
        switch (troop)
        {
            case TW_ENUMS::TroopNames::SPEAR:
                return "spear";
            case TW_ENUMS::TroopNames::SWORD:
                return "sword";
            case TW_ENUMS::TroopNames::AXE:
                return "axe";
            case TW_ENUMS::TroopNames::SPY:
                return "spy";
            case TW_ENUMS::TroopNames::LIGHT:
                return "light";
            case TW_ENUMS::TroopNames::HEAVY:
                return "heavy";
            case TW_ENUMS::TroopNames::RAM:
                return "ram";
            case TW_ENUMS::TroopNames::CATAPULT:
                return "catapult";
            case TW_ENUMS::TroopNames::KNIGHT:
                return "knight";
            case TW_ENUMS::TroopNames::NOBEL:
                return "nobel";
            default:
                return "";
        }
    }

    TW_ENUMS()
    {
    }

    virtual ~TW_ENUMS()
    {
    }
};

#endif
