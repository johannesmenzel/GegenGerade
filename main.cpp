#include <stdio.h>
#include <random>
#include <stdlib.h>

#define TEAM_LIST "FC Bayern München", "FC Schalke 04", "TSG 1899 Hoffenheim", "Borussia Dortmund", "Bayer 04 Leverkusen", "RB Leipzig", "VfB Stuttgart", "Eintracht Frankfurt", "Borussia Mönchengladbach", "Hertha BSC", "Werder Bremen", "FC Augsburg",  "Hannover 96", "FSV Mainz 05", "SC Freiburg", "VfL Wolfsburg", "Fortuna Düsseldorf", "1. FC Nürnberg"
static const double GOALSPERGAME = 2.86;
static const double GOALSPERTEAM = 1.43;
static const double GOALSPERGAME_STDDEV = 1.71;
static const double GOALSPERTEAM_STDDEV = 0.855;

// VALUE GENERATION
int GenerateValues(double median, double stdder) {
    std::random_device rd;
    std::mt19937 gen(rd()); 
    std::normal_distribution<double> distribution(median,stdder);
    int value = (int)distribution(gen);
    //int value = (int) rand() % 20 + 10;
    return value;   
}

// TEAM PROPERTIES
class TeamProperties {
public:
    enum ETeamProperties {
        kAttack = 0,
        kDefense,
        kNumTeamProperties
    }
    TeamProperties() {}
    ~TeamProperties() {}
    void Generate() {
        for (int i=0; i<ETeamProperties::kNumTeamProperties; i++) {
            mTeamProperties[i] = GenerateValues(20., 3.);
        }
    }
    int GetTeamProperties(ETeamProperties property) {
        return mTeamProperties[property];
    }
private:
    int mTeamProperties[kNumTeamProperties];
};

// TEAM LIST
class TeamList {
public:
    TeamList() {}
    ~TeamList() {}
private:
    
};

// TEAM
class Team 
: TeamProperties {
public:
    Team(int id = 0, const char* name = "")
    : mId(id)
    , mName(name)
    {
        TeamProperties::Generate();
    }
    ~Team() {}
    const char* GetName() { return mName; }
private:
    int mId;
    const char* mName;
};

// GAME
class Game {
public:
    Game(Team &teamHome, Team &teamAway)
    : mTeams {teamHome, teamAway}
    , mResult {0, 0}
    , mIsFinished(false)
    {
    }
    ~Game() {}
    
    void Process() {
        if (!mIsFinished) {
            mResult[0] = std::max(GenerateValues(GOALSPERTEAM * ((double)mTeams[0].GetAttack() / (double)mTeams[1].GetDefense()), GOALSPERTEAM_STDDEV), 0);
            mResult[1] = std::max(GenerateValues(GOALSPERTEAM * ((double)mTeams[1].GetAttack() / (double)mTeams[0].GetDefense()), GOALSPERTEAM_STDDEV), 0);
            mIsFinished = true;
        }
    }
    
    void PrintShort() {
        printf(
            "Partie:       %s (%i/%i) - %s (%i/%i) - %i : %i \n"
            , mTeams[0].GetName()
            , mTeams[0].GetAttack()
            , mTeams[0].GetDefense()
            , mTeams[1].GetName()
            , mTeams[1].GetAttack()
            , mTeams[1].GetDefense()
            , mResult[0]
            , mResult[1]
        );
    }
    void PrintLong() {
        printf("Partie:       %s - %s\n", mTeams[0].GetName(), mTeams[1].GetName());
        printf("Angriff:      %i - %i\n", mTeams[0].GetAttack(), mTeams[1].GetAttack());
        printf("Verteidigung: %i - %i\n", mTeams[0].GetDefense(), mTeams[1].GetDefense());
        printf("Ergebnis:     %i : %i\n", mResult[0], mResult[1]);
    }
private:
    Team mTeams[2];
    int mResult[2];
    bool mIsFinished;
};

// MAIN PROGRAM
int main(int argc, char **argv)
{
    Team mTeams[18];
    for (int i=0; i<18; i++) {
        mTeams[i] = Team::Team(i, TEAM_LIST[i]);
    }
    
    Game mGames[9];
    for (int i=0; i<9; i++) {
        mGames[i] = Game(mTeams[2*i], mTeams[2*i+1])
        mGames[i].Process()
    }

return 0;
}
