#pragma once

#include "assert.h"
#include "FrameWork.h"

// C -> string.h
// C++ -> string
#include <string>

using std::wstring;

#include <vector>

using std::vector;

#include <list>

using std::list;

#include <map>

using std::map;

#include <utility>

using std::pair;
using std::make_pair;

#include "GameEngine.h"
#include "Macro.h"
#include "Enum.h"
#include "Structure.h"
#include "Class.h"
#include "Function.h"
#include "PointerFunction.h"
#include "Resource.h"

#include "KeyMGR.h"
#include "PathMGR.h"
#include "SoundMGR.h"
#include "TimeMGR.h"

#include "Sound.h"

#include <commdlg.h>

// �ܼ� ��Ʈ��ó��
#pragma comment(lib, "Msimg32.lib")

// GDI+�� ���� ���� ��ó��
// GDI PLUS
#include <objidl.h>
#include <gdiplus.h>
#include <gdiplusinit.h>
#pragma comment(lib, "Gdiplus.lib")

using namespace Gdiplus;

// ������� ���̺귯��
#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

