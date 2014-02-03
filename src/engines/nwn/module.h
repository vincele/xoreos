/* xoreos - A reimplementation of BioWare's Aurora engine
 *
 * xoreos is the legal property of its developers, whose names can be
 * found in the AUTHORS file distributed with this source
 * distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 *
 * The Infinity, Aurora, Odyssey, Eclipse and Lycium engines, Copyright (c) BioWare corp.
 * The Electron engine, Copyright (c) Obsidian Entertainment and BioWare corp.
 */

/** @file engines/nwn/module.h
 *  The context needed to run a NWN module.
 */

#ifndef ENGINES_NWN_MODULE_H
#define ENGINES_NWN_MODULE_H

#include <list>
#include <set>
#include <map>

#include "common/ustring.h"

#include "aurora/resman.h"

#include "aurora/nwscript/object.h"
#include "aurora/nwscript/objectcontainer.h"

#include "graphics/aurora/types.h"

#include "events/types.h"

#include "engines/nwn/ifofile.h"

namespace Engines {

namespace NWN {

class Area;
class Object;

class GUI;

class Module : public Aurora::NWScript::Object, public Aurora::NWScript::ObjectContainer {
public:
	Module();
	~Module();

	/** Clear the whole context. */
	void clear();

	/** Load a module. */
	bool loadModule(const Common::UString &module);

	void run();

	const Common::UString &getName() const;

	void changeModule(const Common::UString &module);

	static Common::UString getDescription(const Common::UString &module);


private:
	typedef std::map<Common::UString, Area *> AreaMap;

	bool _hasModule; ///< Do we have a module?

	/** Resources added by the module. */
	Aurora::ResourceManager::ChangeID _resModule;

	/** Resources added by the HAKs of the module. */
	std::vector<Aurora::ResourceManager::ChangeID> _resHAKs;

	IFOFile _ifo; ///< The module's IFO.

	GUI *_menu; ///< The ingame main menu.

	// Texture pack
	int _currentTexturePack;
	Aurora::ResourceManager::ChangeID _resTP[4];

	bool _exit; //< Should we exit the module?

	AreaMap         _areas;           ///< The areas in the current module.
	Common::UString _newArea;         ///< The new area to enter.
	Area           *_currentArea;     ///< The current area.

	Engines::NWN::Object *_currentObject; ///< The currently selected object.

	Common::UString _newModule; ///< The module we should change to.


	void unload(); ///< Unload the whole shebang.

	void unloadModule();      ///< Unload the module.
	void unloadHAKs();        ///< Unload the HAKs required by the module.
	void unloadTexturePack(); ///< Unload the texture pack.
	void unloadAreas();       ///< Unload the areas.

	void checkXPs();  ///< Do we have all expansions needed for the module?
	void checkHAKs(); ///< Do we have all HAKs needed for the module?

	void loadHAKs();        ///< Load the HAKs required by the module.
	void loadTexturePack(); ///< Load the texture pack.
	void loadAreas();       ///< Load the areas.

	bool enter();     ///< Enter the currently loaded module.
	void enterArea(); ///< Enter a new area.

	/** Replace the currently running module. */
	bool replaceModule();

	void handleEvents();
	bool handleCamera(const Events::Event &e);
	bool handlePicker(const Events::Event &e);
	bool handleKeys(const Events::Event &e);

	void showMenu();

	void checkCurrentObject();
};

} // End of namespace NWN

} // End of namespace Engines

#endif // ENGINES_NWN_MODULE_H
