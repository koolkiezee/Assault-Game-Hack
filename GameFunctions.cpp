/* We created this namepsace because hacks.cpp became too lenghty,
so we kept some functions here */

#include "GameFunctions.h"

namespace GameFunctions
{
    // Templates

    float(__cdecl *GetFOV)() = (float(__cdecl *)())OFFSET_DYNFOV;

    void(__cdecl *RenderRadarIcon)(float x, float y, float s, int col, int row) = (void(__cdecl *)(float x, float y, float s, int col, int row))0x407E40;

    void(__cdecl *GiveDamage)(int damage, Player *target, Player *actor, int gun, bool gib, bool local) = (void(__cdecl *)(int damage, Player *target, Player *actor, int gun, bool gib, bool local))OFFSET_GIVEDAMAGE;

    // Functions
    bool GotTeamMates()
    {
        DWORD dwGameMode = *reinterpret_cast<DWORD *>(OFFSET_GAMEMODE);
        return (
            dwGameMode == GMODE_BOTTEAMONESHOTONKILL ||
            dwGameMode == GMODE_TEAMONESHOTONEKILL ||
            dwGameMode == GMODE_BOTTEAMDEATHMATCH ||
            dwGameMode == GMODE_TEAMDEATHMATCH ||
            dwGameMode == GMODE_TEAMSURVIVOR ||
            dwGameMode == GMODE_TEAMLSS ||
            dwGameMode == GMODE_CTF ||
            dwGameMode == GMODE_TEAMKEEPTHEFLAG ||
            dwGameMode == GMODE_HUNTTHEFLAG ||
            dwGameMode == GMODE_TEAMPF ||
            dwGameMode == GMODE_BOTTEAMSURVIVOR ||
            dwGameMode == GMODE_BOTTEAMONESHOTONKILL);
    }

    void AddHudLine(char *pText)
    {
        typedef void(__cdecl * thudoutf)(char *pText);
        thudoutf ohudoutf = reinterpret_cast<thudoutf>(OFFSET_HUDOUTF);

        ohudoutf(pText);
    }

    bool WorldToScreen(Vec3 vPos, Vec3 *pvOut)
    {
        ScreenSettings *pScreenSettings = ScreenSettings::GetInstance();
        if (!ExtraFunctions::IsValidPtr(pScreenSettings))
            return false;

        glmatrixf *mvpmatrix = reinterpret_cast<glmatrixf *>(OFFSET_MVPMATRIX);

        float mX = (float)pScreenSettings->m_Width / 2.0F;
        float mY = (float)pScreenSettings->m_Height / 2.0F;

        float x = mvpmatrix->transformx(vPos);
        float y = mvpmatrix->transformy(vPos);
        float z = mvpmatrix->transformz(vPos);
        float w = mvpmatrix->transformw(vPos);

        if (w < 0.01F)
            return false;

        pvOut->x = mX + (mX * x / w);
        pvOut->y = mY - (mY * y / w);
        pvOut->z = w;

        return true;
    }

    void EngineDrawString(char *pText, int x, int y, int r, int g, int b, int pUnknown, int pUnknown2)
    {
        __asm
        {
            push pUnknown2;
            push pUnknown;
            push b;
            push r;
            push y;
            push x;
            push pText;
            mov eax, g;
            mov ecx, OFFSET_ENGINE_DRAWTEXT;
            call ecx;
            add esp, 0x1C;
        }
    }

    bool IsVisible(Vec3 vFrom, Vec3 vTo)
    {
        __asm
        {
            push vTo.z;
            push vTo.y;
            push vTo.x;

            push vFrom.z;
            push vFrom.y;
            push vFrom.x;

            xor cl, cl; // Tracer
            xor eax, eax;
            mov ebx, OFFSET_ISVISIBLE;
            call ebx;
            add esp, 0x18;
        }
    }

    void DrawString(int x, int y, int r, int g, int b, char *pText, ...)
    {
        va_list va_alist;

        char buf[256];

        va_start(va_alist, pText);
        _vsnprintf_s(buf, sizeof(buf), pText, va_alist);
        va_end(va_alist);

        float extraScale = 0.3F;

        glScalef(extraScale, extraScale, 1);

        EngineDrawString(buf, static_cast<int>(x / extraScale), static_cast<int>(y / extraScale), r, g, b);

        glScalef(1 / extraScale, 1 / extraScale, 1);
    }

    void PatchRecoil(bool bNoRecoil)
    {
        if (bNoRecoil)
            ExtraFunctions::MemoryEdit(reinterpret_cast<void *>(OFFSET_PATCHRECOIL), reinterpret_cast<BYTE *>("\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"), 10);
        else
            ExtraFunctions::MemoryEdit(reinterpret_cast<void *>(OFFSET_PATCHRECOIL), reinterpret_cast<BYTE *>("\x50\x8D\x4C\x24\x1C\x51\x8B\xCE\xFF\xD2"), 10);
    }
}