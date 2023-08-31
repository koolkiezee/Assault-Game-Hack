#include "Hacks.h"
#include "MenuFunctions.h"
#include "GameFunctions.h"

using namespace AssaultCube;
using namespace ExtraFunctions;

CMenu *g_MenuFunctions = NULL;

void OnInitialize()
{
    g_MenuFunctions = new CMenu();

    g_MenuFunctions->AddHack(new CHack("Enemy position", false));
    g_MenuFunctions->AddHack(new CHack("Fly", false));
    g_MenuFunctions->AddHack(new CHack("No Recoil", false));
    g_MenuFunctions->AddHack(new CHack("Equipments", false));

    GameFunctions::AddHudLine("Hack loaded.");
}

void OnHackSet(CHack *pHack)
{
    // Disable fly mode once.
    if (!_stricmp(pHack->GetName(), "Fly") && !pHack->GetEnabled() && Game::GetInstance() && Game::GetInstance()->m_LocalPlayer)
    {
        Game::GetInstance()->m_LocalPlayer->m_SpectateMode = SM_NONE;
    }

    // calls Patch Recoil to change memory address
    if (!_stricmp(pHack->GetName(), "No Recoil"))
    {
        GameFunctions::PatchRecoil(pHack->GetEnabled());
    }
}

/* draw a rectangle around the user */

void DrawRect(int x, int y, int x2, int y2, Color32 color, bool bFilled)
{
    glDepthMask(GL_FALSE);
    glDisable(GL_TEXTURE_2D);

    glColor4f(color.r, color.g, color.b, color.a);

    glBegin(bFilled ? GL_QUADS : GL_LINE_LOOP);

    glVertex2f(x, y);
    glVertex2f(x2, y);
    glVertex2f(x2, y2);
    glVertex2f(x, y2);

    glEnd();

    glEnable(GL_TEXTURE_2D);
    glDepthMask(GL_TRUE);
}

void DrawLine(int x, int y, int x2, int y2, float width, Color32 color)
{
    glDepthMask(GL_FALSE);
    glDisable(GL_TEXTURE_2D);

    glLineWidth(width);
    glColor4f(color.r, color.g, color.b, color.a);

    glBegin(GL_LINES);

    glVertex2f(x, y);
    glVertex2f(x2, y2);

    glEnd();

    glEnable(GL_TEXTURE_2D);
    glDepthMask(GL_TRUE);
}

/* draw a healthbar over the enemy */

void DrawHealthBar(int x, int y, int w, int h, float health, Color32 color)
{
    // Outline
    DrawRect(x, y, x + w, y + h, Color32(0.0F, 0.0F, 0.0F, 1.0F));

    // Content
    DrawRect(x + 1, y + 1, x + (w * health) - 1, y + h - 1, color);
}

/* used to project the menu on the screen */

void MenuFunctionsRender()
{
    glPushMatrix();

    float flScale = 0.8F;

    glScalef(flScale, flScale, 1.0F);

    int MenuFunctionsX = 700;
    int MenuFunctionsY = 180;
    int MenuFunctionsYOFFSET = 20;
    int MenuFunctionsOPTOFFSET = 200;

    GameFunctions::DrawString(MenuFunctionsX, MenuFunctionsY - 30, 255, 255, 0, "AssaultCube Hacks menu");

    int i = 0;
    for (auto item = g_MenuFunctions->GetHacks().begin(); item != g_MenuFunctions->GetHacks().end(); ++item) // to display hacks menu on the in-game screen
    {
        CHack *pHack = *item._Ptr; // item->second;

        if (i == g_MenuFunctions->GetSelectedIndex())
        {
            GameFunctions::DrawString(MenuFunctionsX, MenuFunctionsY + MenuFunctionsYOFFSET * i, 255, 0, 0, pHack->GetName());
            GameFunctions::DrawString(MenuFunctionsX + MenuFunctionsOPTOFFSET, MenuFunctionsY + MenuFunctionsYOFFSET * i, 255, 50, 50, pHack->GetEnabled() ? "On" : "Off");
        }
        else
        {
            GameFunctions::DrawString(MenuFunctionsX, MenuFunctionsY + MenuFunctionsYOFFSET * i, 255, 0, 255, pHack->GetName());
            GameFunctions::DrawString(MenuFunctionsX + MenuFunctionsOPTOFFSET, MenuFunctionsY + MenuFunctionsYOFFSET * i, 150, 150, 150, pHack->GetEnabled() ? "On" : "Off");
        }

        ++i;
    }

    glScalef(1 / flScale, 1 / flScale, 1.0F);

    glPopMatrix();
}

void MenuFunctionsInput() // for movement in the hack menu and on/off option
{
    if (GetAsyncKeyState(VK_DOWN) & 1)
    {
        if (g_MenuFunctions->GetSelectedIndex() < static_cast<int>(g_MenuFunctions->GetHacks().size()) - 1)
            g_MenuFunctions->SetSelectedIndex(g_MenuFunctions->GetSelectedIndex() + 1);
    }

    if (GetAsyncKeyState(VK_UP) & 1)
    {
        if (g_MenuFunctions->GetSelectedIndex() > 0)
            g_MenuFunctions->SetSelectedIndex(g_MenuFunctions->GetSelectedIndex() - 1);
    }

    if (GetAsyncKeyState(VK_RIGHT) & 1)
    {
        CHack *pHack = g_MenuFunctions->GetHacks().at(g_MenuFunctions->GetSelectedIndex());
        pHack->SetEnabled(true);
        OnHackSet(pHack);
    }

    if (GetAsyncKeyState(VK_LEFT) & 1)
    {
        CHack *pHack = g_MenuFunctions->GetHacks().at(g_MenuFunctions->GetSelectedIndex());
        pHack->SetEnabled(false);
        OnHackSet(pHack);
    }
}

void DrawESP(Player *pTargetPlayer, Player *pLocalPlayer) // locating the enemy.
{
    Vec3 vHeadPos = pTargetPlayer->m_HeadPos;
    Vec3 vFootPos = pTargetPlayer->m_FootPos;

    vHeadPos.z += 0.8F; // Regular head pos is not high enough

    Vec3 vScreenHead, vScreenFoot;
    if (GameFunctions::WorldToScreen(vHeadPos, &vScreenHead) && GameFunctions::WorldToScreen(vFootPos, &vScreenFoot))
    {
        float flHeight = abs(vScreenFoot.y - vScreenHead.y);
        float flWidth = flHeight / 2.0F;

        Color32 color = GameFunctions::IsVisible(pLocalPlayer->m_HeadPos, pTargetPlayer->m_HeadPos) ? Color32(1.0F, 1.0F, 0.0F, 1.0F) : Color32(1.0F, 0.0F, 0.0F, 1.0F);

        DrawRect(vScreenHead.x - flWidth / 2, vScreenHead.y, vScreenHead.x + flWidth / 2, vScreenHead.y + flHeight, color, false);

        DrawHealthBar(vScreenHead.x - flWidth / 2, vScreenHead.y - 14, flWidth, 6.0F, (float)((float)pTargetPlayer->m_Health / 100.0F), Color32(0.0F, 1.0F, 0.0F, 1.0F));

        GameFunctions::DrawString(vScreenFoot.x - flWidth / 2, vScreenFoot.y + 4, (int)(color.r * 255), (int)(color.g * 255), (int)(color.b * 255), pTargetPlayer->m_Name);
    }
}

void OnRenderFrame()
{

    MenuFunctionsRender(); // project menu on screen
    MenuFunctionsInput();  // called to enable input on menu

    Game *pGame = Game::GetInstance();
    if (!IsValidPtr(pGame))
        return;

    Player *pLocalPlayer = pGame->m_LocalPlayer;

    if (g_MenuFunctions->GetHack("Fly")->GetEnabled())
    {
        pLocalPlayer->m_SpectateMode = SM_FLY;
    }

    /* implementation of enemy position hack when it is enabled on menu */

    if (g_MenuFunctions->GetHack("Enemy position")->GetEnabled())
    {
        for (int i = 0; i < pGame->m_PlayerCount; i++)
        {
            Player *pPlayer = pGame->GetPlayer(i);
            if (!IsValidPtr(pPlayer))
                continue;

            if (pPlayer == pLocalPlayer)
                continue;

            if (pPlayer->m_State != CS_ALIVE)
                continue;

            if (pPlayer->m_Health <= 0 || pPlayer->m_Health > 100)
                continue;

            if (pPlayer->m_HeadPos.x == 0 && pPlayer->m_HeadPos.y == 0 && pPlayer->m_HeadPos.z == 0)
                continue;

            if (GameFunctions::GotTeamMates())
            {
                if (pLocalPlayer->m_Team == pPlayer->m_Team) // No Teammates
                    continue;
            }

            DrawESP(pPlayer, pLocalPlayer);
        }
    }

    /* implementation of equipments hack when it is enabled on menu */

    if (g_MenuFunctions->GetHack("Equipments")->GetEnabled())
    {
        EntityList *pEntities = EntityList::GetInstance();
        if (IsValidPtr(pEntities))
        {
            for (int i = 0; i < pEntities->m_EntityCount; i++)
            {
                Entity *pEntity = pEntities->GetEntity(i);
                if (!IsValidPtr(pEntity))
                    continue;

                // Only visible items
                if (pEntity->spawned == FALSE)
                    continue;

                // very ugly way but this is what the engine does because the items bounce slightly up and down
                float flNewZ = (float)(1 + sinf(*reinterpret_cast<DWORD *>(OFFSET_LASTMILLIS) / 100.0f + pEntity->x + pEntity->y) / 20);
                // fix height according to the map data
                flNewZ += (&(*reinterpret_cast<sqr **>(OFFSET_WORLD))[((pEntity->y) << (*reinterpret_cast<DWORD *>(OFFSET_SFACTOR))) + (pEntity->x)])->floor + pEntity->attr1;

                Vec3 vPos = Vec3(pEntity->x, pEntity->y, flNewZ);

                Vec3 vScreen;
                if (GameFunctions::WorldToScreen(vPos, &vScreen))
                {
                    switch (pEntity->type)
                    {
                    case I_HEALTH:
                        GameFunctions::DrawString(vScreen.x, vScreen.y, 255, 255, 255, "[Health]");
                        break;
                    case I_AMMO:
                        GameFunctions::DrawString(vScreen.x, vScreen.y, 255, 255, 255, "[Ammo]");
                        break;
                    case I_AKIMBO:
                        GameFunctions::DrawString(vScreen.x, vScreen.y, 255, 255, 255, "[Akimbo]");
                        break;
                    case I_ARMOUR:
                        GameFunctions::DrawString(vScreen.x, vScreen.y, 255, 255, 255, "[Armor]");
                        break;
                    case CTF_FLAG:
                        GameFunctions::DrawString(vScreen.x, vScreen.y, 255, 255, 255, "[Flag]");
                        break;
                    case I_GRENADE:
                        GameFunctions::DrawString(vScreen.x, vScreen.y, 255, 255, 255, "[Grenade]");
                        break;
                    default:
                        break;
                    }
                }
            }
        }
    }
}
