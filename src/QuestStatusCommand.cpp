#include "AccountMgr.h"
#include "Chat.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "Config.h"
#include "Language.h"


class AnnouncePlayer : public PlayerScript{

public:
    AnnouncePlayer() : PlayerScript("AnnouncePlayer") { }

    void OnLogin(Player* player) override
    {
        if (sConfigMgr->GetOption<bool>("AnnouncePlayer.enable", true))
        {
            ChatHandler(player->GetSession()).SendSysMessage("This server is running the |cff4CFF00Quest Status |rmodule.");
        }
    }
};

class QuestStatusCommand : public CommandScript
{
    public:

        QuestStatusCommand() : CommandScript("QuestStatusCommand") { }

        std::vector<ChatCommand> GetCommands() const override
        {
            static std::vector<ChatCommand> commandTable
            {
                { "", SEC_MODERATOR, false, &HandleQuestStatusByIdCommand, "" }
            };

            static std::vector<ChatCommand> questCommandTable =
            {
                { "qs",    SEC_MODERATOR, false, nullptr, "", commandTable}
            };

            return questCommandTable;

        }

        static bool HandleQuestStatusByIdCommand(ChatHandler* handler, const char* args)
        {
            if (!*args)
                return false;

            bool found = false;

            Player* target = handler->getSelectedPlayerOrSelf();

            uint32 id = atoi((char*)args);

            if (Quest const* quest = sObjectMgr->GetQuestTemplate(id))
            {

                std::string title = quest->GetTitle();
                if (title.empty())
                    return false;

                char const* statusStr = "";

                if (target)
                {

                    QuestStatus status = target->GetQuestStatus(quest->GetQuestId());

                    switch (status)
                    {
                        case QUEST_STATUS_COMPLETE:
                            statusStr = handler->GetAcoreString(LANG_COMMAND_QUEST_COMPLETE);
                            break;
                        case QUEST_STATUS_INCOMPLETE:
                            statusStr = handler->GetAcoreString(LANG_COMMAND_QUEST_ACTIVE);
                            break;
                        case QUEST_STATUS_REWARDED:
                            statusStr = handler->GetAcoreString(LANG_COMMAND_QUEST_REWARDED);
                            break;
                        default:
                            break;
                    }
                }

                if (handler->GetSession())
                    handler->PSendSysMessage(LANG_QUEST_LIST_CHAT, quest->GetQuestId(), quest->GetQuestId(), quest->GetQuestLevel(), title.c_str(), statusStr);
                else
                    handler->PSendSysMessage(LANG_QUEST_LIST_CONSOLE, quest->GetQuestId(), title.c_str(), statusStr);

                found = true;
            }

            if (!found)
                handler->SendSysMessage(LANG_COMMAND_NOQUESTFOUND);

            return true;
        }

};

void AddSC_Quest_Status_Scripts()
{
    new AnnouncePlayer();
    new QuestStatusCommand();
}
