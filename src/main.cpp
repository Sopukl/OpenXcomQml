/*
 * Copyright 2010-2016 OpenXcom Developers.
 *
 * This file is part of OpenXcom.
 *
 * OpenXcom is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenXcom is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenXcom.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <exception>
#include <cassert>
#include "version.h"
#include "Engine/Exception.h"
#include "Engine/Logger.h"
#include "Engine/CrossPlatform.h"
#include "Engine/Options.h"
#include "Engine/FileMap.h"
#include "Menu/StartState.h"
#include "Savegame/SavedGame.h"
#include "Savegame/Base.h"
#include "Savegame/Soldier.h"
#include "Geoscape/GeoscapeState.h"
#include <QGuiApplication>
#include "GameRenderer.h"
#include "XcomImagesProvider.h"
#include <QQuickWindow>
#include <QQmlApplicationEngine>
#include <QQuickStyle>

/** @mainpage
 * @author OpenXcom Developers
 *
 * OpenXcom is an open-source clone of the original X-Com
 * written entirely in C++ and SDL. This documentation contains info
 * on every class contained in the source code and its public methods.
 * The code itself also contains in-line comments for more complicated
 * code blocks. Hopefully all of this will make the code a lot more
 * readable for you in case you which to learn or make use of it in
 * your own projects, though note that all the source code is licensed
 * under the GNU General Public License. Enjoy!
 */

using namespace OpenXcom;

// Crash handling routines
#ifdef _MSC_VER

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <windows.h>

LONG WINAPI crashLogger(PEXCEPTION_POINTERS exception)
{
	CrossPlatform::crashDump(exception, "");
	return EXCEPTION_CONTINUE_SEARCH;
}
#else
#include <signal.h>
void signalLogger(int sig)
{
	CrossPlatform::crashDump(&sig, "");
	exit(EXIT_FAILURE);
}

#endif

void exceptionLogger()
{
	static bool logged = false;
	std::string error;
	try
	{
		if (!logged)
		{
			logged = true;
			throw;
		}
	}
	catch (const std::exception &e)
	{
		error = e.what();
	}
	catch (...)
	{
		error = "Unknown exception";
	}
	CrossPlatform::crashDump(0, error);
	exit(EXIT_FAILURE);
}

// If you can't tell what the main() is for you should have your
// programming license revoked...
int main(int argc, char *argv[])
{
	QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGL);
	QGuiApplication app(argc, argv);
	QQuickStyle::setStyle("Universal");

	qmlRegisterType<OpenXcom::GameRenderer>("OpenXcom", 1, 0, "GameRenderer");
	qmlRegisterType<OpenXcom::GeoscapeState>("OpenXcom", 1, 0, "GeoscapeState");
	qmlRegisterType<OpenXcom::SavedGame>("OpenXcom", 1, 0, "SavedGame");
	qmlRegisterType<OpenXcom::Target>("OpenXcom", 1, 0, "Target");
	qmlRegisterType<OpenXcom::Base>("OpenXcom", 1, 0, "Base");
	qmlRegisterType<OpenXcom::Soldier>("OpenXcom", 1, 0, "Soldier");
	qmlRegisterType<OpenXcom::Craft>("OpenXcom", 1, 0, "Craft");
	qmlRegisterType<OpenXcom::Country>("OpenXcom", 1, 0, "Country");
	qmlRegisterType<OpenXcom::Options1>("OpenXcom", 1, 0, "Options1");
	qmlRegisterSingletonType<Options1>("OpenXcom", 1, 0, "Options1",
		[](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject* {
			Q_UNUSED(engine)
			Q_UNUSED(scriptEngine)
			QQmlEngine::setObjectOwnership(&options1, QQmlEngine::CppOwnership);
		   return &options1;
	});
	qmlRegisterSingletonType<Game>("OpenXcom", 1, 0, "Game",
		[](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject* {
		   Q_UNUSED(engine)
		   Q_UNUSED(scriptEngine)
		   QQmlEngine::setObjectOwnership(&game, QQmlEngine::CppOwnership);
		   return &game;
	});
	QQmlApplicationEngine engine;
	engine.addImageProvider("xcom", new XcomImagesProvider);
	engine.addImportPath("qrc:/");
	YAML::setGlobalErrorHandler();
	CrossPlatform::getErrorDialog();
	CrossPlatform::processArgs(argc, argv);
	if (!Options::init())
		return EXIT_SUCCESS;
	options1.baseXResolution = options1.displayWidth();
	options1.baseYResolution = options1.displayHeight();
	game.init();

	engine.load(QUrl("qrc:/main.qml"));

	return app.exec();
}

namespace OpenXcom
{
	Exception::Exception(const std::string &msg) : runtime_error(msg) {
#ifdef DUMP_CORE
		__builtin_trap();
#endif
	}
}

#ifdef __MORPHOS__
const char Version[] = "$VER: OpenXCom " OPENXCOM_VERSION_SHORT " (" __AMIGADATE__  ")";
#endif



#ifndef NDEBUG

#include "Engine/Collections.h"
#include "fmath.h"

struct BadMove
{
	int i;

	BadMove(int b)
	{
		i = b;
	}
	BadMove(BadMove&& b)
	{
		i = b.i;
		b.i = {};
	}
	BadMove(const BadMove& b)
	{
		i = b.i;
	}

	BadMove& operator=(BadMove&& b)
	{
		i = {}; //this can reset other `b` too if we do not check for `this == &b`
		i = b.i;
		b.i = {}; //same there
		return *this;
	}

	bool operator==(const BadMove& b) const
	{
		return i == b.i;
	}
};

static auto dummy = ([]
{
	{
		std::vector<int> v = { 1, 2, 3, 4 };
		Collections::removeIf(v, [](int& i) { return i < 3; });
		assert((v == std::vector<int>{ 3, 4 }));
	}
	{
		std::vector<int> v = { 1, 2, 3, 4 };
		Collections::removeIf(v, [](int& i) { return i > 2; });
		assert((v == std::vector<int>{ 1, 2 }));
	}
	{
		std::vector<int> v = { 1, 2, 3, 4 };
		Collections::removeIf(v, [](int& i) { return i < 2 || i == 4; });
		assert((v == std::vector<int>{ 2, 3 }));
	}
	{
		std::vector<int> v = { 1, 2, 3, 4 };
		Collections::removeIf(v, [](int& i) { if (i < 2 || i == 4) { return true; } else { i += 10; return false; } });
		assert((v == std::vector<int>{ 12, 13 }));
	}
	{
		std::vector<int> v = { 1, 2, 3, 4 };
		Collections::removeIf(v, [](int& i) { return false; });
		assert((v == std::vector<int>{ 1, 2, 3, 4 }));
	}
	{
		std::vector<int> v = { 1, 2, 3, 4 };
		Collections::removeIf(v, [](int& i) { return true; });
		assert((v == std::vector<int>{ }));
	}
	{
		std::vector<int> v = { 1, 2, 3, 4 };
		Collections::removeIf(v, [](int& i) { i += 10; return false; });
		assert((v == std::vector<int>{ 11, 12, 13, 14 }));
	}

	{
		std::vector<BadMove> v = { 1, 2, 3, 4 };
		Collections::removeIf(v, [](BadMove& i) { return i.i < 3; });
		assert((v == std::vector<BadMove>{ 3, 4 }));
	}
	{
		std::vector<BadMove> v = { 1, 2, 3, 4 };
		Collections::removeIf(v, [](BadMove& i) { return i.i > 2; });
		assert((v == std::vector<BadMove>{ 1, 2 }));
	}
	{
		std::vector<BadMove> v = { 1, 2, 3, 4 };
		Collections::removeIf(v, [](BadMove& i) { if (i.i < 2 || i.i == 4) { return true; } else { i.i += 10; return false; } });
		assert((v == std::vector<BadMove>{ 12, 13 }));
	}
	{
		std::vector<BadMove> v = { 1, 2, 3, 4 };
		Collections::removeIf(v, [](BadMove& i) { return false; });
		assert((v == std::vector<BadMove>{ 1, 2, 3, 4 }));
	}
	{
		std::vector<BadMove> v = { 1, 2, 3, 4 };
		Collections::removeIf(v, [](BadMove& i) { i.i += 10; return false; });
		assert((v == std::vector<BadMove>{ 11, 12, 13, 14 }));
	}
	{
		std::vector<BadMove> v = { 1, 2, 3, 4 };
		Collections::removeIf(v, [](BadMove& i) { return true; });
		assert((v == std::vector<BadMove>{ }));
	}

	return 0;
})();

struct DummyVectDouble
{
	double x, y, z;

	bool operator==(const DummyVectDouble& a) const { return AreSame(x, a.x) && AreSame(y, a.y) && AreSame(z, a.z); };
};

static auto dummyMath = ([]
{
	const DummyVectDouble x { 1, 0, 0 };
	const DummyVectDouble y { 0, 1, 0 };
	const DummyVectDouble z { 0, 0, 1 };

	const DummyVectDouble x256 { 256, 0, 0 };
	const DummyVectDouble y256 { 0, 256, 0 };
	const DummyVectDouble z256 { 0, 0, 256 };

	assert(x == VectNormalize(x));
	assert(y == VectNormalize(y));
	assert(z == VectNormalize(z));
	assert(x == VectNormalize(x256));
	assert(y == VectNormalize(y256));
	assert(z == VectNormalize(z256));
	assert(x256 == VectNormalize(x256, 256));
	assert(y256 == VectNormalize(y256, 256));
	assert(z256 == VectNormalize(z256, 256));

	assert(z == VectCrossProduct(x, y));
	assert(x == VectCrossProduct(y, z));
	assert(y == VectCrossProduct(z, x));

	assert(z256 == VectCrossProduct(x256, y));
	assert(x256 == VectCrossProduct(y256, z));
	assert(y256 == VectCrossProduct(z256, x));

	assert(z256 == VectCrossProduct(x256, y256, 256));
	assert(x256 == VectCrossProduct(y256, z256, 256));
	assert(y256 == VectCrossProduct(z256, x256, 256));

	return 0;
})();

#endif
