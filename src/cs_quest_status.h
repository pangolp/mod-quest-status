#include "AccountMgr.h"
#include "Chat.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "Config.h"
#include "Language.h"

using namespace Acore::ChatCommands;

class AnnouncePlayer : public PlayerScript
{
public:
    AnnouncePlayer() : PlayerScript("AnnouncePlayer") {}

    void OnLogin(Player* player) override;
};

class QuestStatusCommand : public CommandScript
{
public:
    QuestStatusCommand() : CommandScript("QuestStatusCommand") {}

    ChatCommandTable GetCommands() const override;
    static bool HandleQuestStatusByIdCommand(ChatHandler* handler, uint32 itemId);
};

void AddQuestStatusCommandScripts()
{
    new AnnouncePlayer();
    new QuestStatusCommand();
}
