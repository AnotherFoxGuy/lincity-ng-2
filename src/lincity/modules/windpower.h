
#define GROUP_WIND_POWER_COLOUR (green(25))
#define GROUP_WIND_POWER_COST   20000
#define GROUP_WIND_POWER_COST_MUL 25
#define GROUP_WIND_POWER_BUL_COST   1000
#define GROUP_WIND_POWER_TECH   30
#define GROUP_WIND_POWER_FIREC  10
#define GROUP_WIND_POWER_RANGE  0
#define GROUP_WIND_POWER_SIZE  2

#define WIND_POWER_MWH        450
#define WIND_POWER_JOBS       15
#define MAX_JOBS_AT_WIND_POWER 20*(WIND_POWER_JOBS)
#define MAX_MWH_AT_WIND_POWER 20*(WIND_POWER_MWH)
/* WIND_POWER_RCOST is days per quid */
#define WIND_POWER_RCOST      2
#define WIND_POWER_ANIM_SPEED 120

#define WIND_POWER_TECH 450000

#include "modules.h"
#include "../lintypes.h"
#include "../lctypes.h"

class WindpowerConstructionGroup: public ConstructionGroup {
public:
    WindpowerConstructionGroup(
        const char *name,
        unsigned short no_credit,
        unsigned short group,
        unsigned short size, int colour,
        int cost_mul, int bul_cost, int fire_chance,
        int cost, int tech, int range
    ): ConstructionGroup(
        name, no_credit, group, size, colour, cost_mul, bul_cost, fire_chance,
        cost, tech, range, 2/*mps_pages*/
    ) {
        commodityRuleCount[STUFF_JOBS].maxload = MAX_JOBS_AT_WIND_POWER;
        commodityRuleCount[STUFF_JOBS].take = true;
        commodityRuleCount[STUFF_JOBS].give = false;
        commodityRuleCount[STUFF_MWH].maxload = MAX_MWH_AT_WIND_POWER;
        commodityRuleCount[STUFF_MWH].take = false;
        commodityRuleCount[STUFF_MWH].give = true;
    }
    // overriding method that creates a Windpower
    virtual Construction *createConstruction(int x, int y);
};

extern WindpowerConstructionGroup windpowerConstructionGroup;
extern WindpowerConstructionGroup windpower_RG_ConstructionGroup;
extern WindpowerConstructionGroup windpower_G_ConstructionGroup;

class Windpower: public RegisteredConstruction<Windpower> { // Windpower inherits from its own RegisteredConstruction
public:
    Windpower(int x, int y, ConstructionGroup *cstgrp): RegisteredConstruction<Windpower>(x, y)
    {
        this->constructionGroup = cstgrp;
        init_resources();
        // this->anim = 0;
        this->animate_enable = false;
        this->tech = tech_level;
        setMemberSaved(&this->tech, "tech");
        this->working_days = 0;
        this->busy = 0;
        // this->mwh_output = (int)(WIND_POWER_MWH + (((double)tech_level * WIND_POWER_MWH) / MAX_TECH_LEVEL));
        setMemberSaved(&this->mwh_output, "mwh_output"); // compatibility
        initialize_commodities();

        commodityMaxCons[STUFF_JOBS] = 100 * WIND_POWER_JOBS;
        // commodityMaxProd[STUFF_MWH] = 100 * mwh_output;
    }

    virtual void initialize() override {
        RegisteredConstruction::initialize();

        this->mwh_output = (int)(WIND_POWER_MWH +
          (((double)tech_level * WIND_POWER_MWH) / MAX_TECH_LEVEL));

        commodityMaxProd[STUFF_MWH] = 100 * mwh_output;
    }

    virtual ~Windpower() { }
    virtual void update() override;
    virtual void report() override;
    virtual void animate() override;

    int  mwh_output;
    int  tech;
    int  anim;
    int  working_days, busy;
    bool animate_enable;
};

/** @file lincity/modules/windmill.h */
