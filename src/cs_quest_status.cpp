#include "cs_quest_status.h"

void AnnouncePlayer::OnLogin(Player* player)
{
    if (sConfigMgr->GetOption<bool>("AnnouncePlayer.enable", true))
    {
        std::string messageModule = "";

        switch (player->GetSession()->GetSessionDbLocaleIndex())
        {
            case LOCALE_enUS:
            case LOCALE_koKR:
            case LOCALE_frFR:
            case LOCALE_deDE:
            case LOCALE_zhCN:
            case LOCALE_zhTW:
            case LOCALE_ruRU:
            {
                messageModule = "This server is running the |cff4CFF00Quest Status |rmodule.";
                break;
            }

            case LOCALE_esES:
            case LOCALE_esMX:
            {
                messageModule = "Este servidor está ejecutando el módulo |cff4CFF00Quest Status|r";
                break;
            }

            default:
                break;
        }

        ChatHandler(player->GetSession()).SendSysMessage(messageModule);
    }
}

ChatCommandTable QuestStatusCommand::GetCommands() const
{
    static ChatCommandTable qsCommandTable =
    {
        { "", HandleQuestStatusByIdCommand, SEC_MODERATOR, Console::No }
    };

    static ChatCommandTable questCommandTable =
    {
        { "qs", qsCommandTable }
    };

    return questCommandTable;
}

bool QuestStatusCommand::HandleQuestStatusByIdCommand(ChatHandler* handler, uint32 questId)
{
    if (!questId)
    {
        handler->SendErrorMessage("The script requires as a parameter the id of the quest to search.");
        return false;
    }

    bool found = false;

    Player* target = handler->getSelectedPlayerOrSelf();

    if (Quest const* quest = sObjectMgr->GetQuestTemplate(questId))
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
                case QUEST_STATUS_NONE:
                    statusStr = " [None]";
                    break;
                case QUEST_STATUS_COMPLETE:
                    statusStr = " [Complete]";
                    break;
                case QUEST_STATUS_INCOMPLETE:
                    statusStr = " [Incomplete]";
                    break;
                case QUEST_STATUS_FAILED:
                    statusStr = " [Failed]";
                    break;
                case QUEST_STATUS_REWARDED:
                    statusStr = " [Rewarded]";
                    break;
                default:
                    break;
            }
        }

        if (handler->GetSession())
            handler->PSendSysMessage("ID: %d - Level: %d - Name: %s - Status: %s", quest->GetQuestId(), quest->GetQuestLevel(), title.c_str(), statusStr);

        found = true;
    }

    if (!found)
        handler->SendSysMessage(LANG_COMMAND_NOQUESTFOUND);

    return true;
}
