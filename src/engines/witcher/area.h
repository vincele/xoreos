/* xoreos - A reimplementation of BioWare's Aurora engine
 *
 * xoreos is the legal property of its developers, whose names
 * can be found in the AUTHORS file distributed with this source
 * distribution.
 *
 * xoreos is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * xoreos is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with xoreos. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file
 *  An area in The Witcher.
 */

#ifndef ENGINES_WITCHER_AREA_H
#define ENGINES_WITCHER_AREA_H

#include "src/common/types.h"
#include "src/common/ustring.h"
#include "src/common/mutex.h"

#include "src/aurora/types.h"

#include "src/aurora/nwscript/object.h"

#include "src/graphics/aurora/types.h"

#include "src/sound/types.h"

#include "src/events/types.h"
#include "src/events/notifyable.h"

namespace Engines {

namespace Witcher {

class Module;

class Object;

class Area : public Aurora::NWScript::Object, public Events::Notifyable {
public:
	Area(Module &module, const Common::UString &resRef);
	~Area();

	// General properties

	/** Return the area's resref (resource ID). */
	const Common::UString &getResRef();
	/** Return the area's localized name. */
	const Common::UString &getName();

	// Visibility

	void show(); ///< Show the area.
	void hide(); ///< Hide the area.

	// Music/Sound

	uint32 getMusicDayTrack   () const; ///< Return the music track ID playing by day.
	uint32 getMusicNightTrack () const; ///< Return the music track ID playing by night.
	uint32 getMusicBattleTrack() const; ///< Return the music track ID playing in battle.

	void setMusicDayTrack   (uint32 track); ///< Set the music track ID playing by day.
	void setMusicNightTrack (uint32 track); ///< Set the music track ID playing by night.
	void setMusicBattleTrack(uint32 track); ///< Set the music track ID playing in battle.

	void stopAmbientMusic(); ///< Stop the ambient music.

	/** Play the specified music (or the area's default) as ambient music. */
	void playAmbientMusic(Common::UString music = "");

	// Events

	/** Add a single event for consideration into the area event queue. */
	void addEvent(const Events::Event &event);
	/** Process the current event queue. */
	void processEventQueue();

	/** Forcibly remove the focus from the currently highlighted object. */
	void removeFocus();


	/** Return the localized name of an area. */
	static Common::UString getName(const Common::UString &resRef);


protected:
	/** Notify the area that the camera has been moved. */
	void notifyCameraMoved();


private:
	typedef std::list<Engines::Witcher::Object *> ObjectList;
	typedef std::map<uint32, Engines::Witcher::Object *> ObjectMap;


	Module *_module;

	bool _loaded;

	Common::UString _resRef; ///< The area's resref (resource ID).
	Common::UString _name;   ///< The area's localized name.

	uint32 _musicDayTrack;    ///< Music track ID that plays by day.
	uint32 _musicNightTrack;  ///< Music track ID that plays by night.
	uint32 _musicBattleTrack; ///< Music track ID that plays in battle.

	Common::UString _musicDay;    ///< Music that plays by day.
	Common::UString _musicNight;  ///< Music that plays by night.
	Common::UString _musicBattle; ///< Music that plays in battle.

	bool _visible; ///< Is the area currently visible?

	Sound::ChannelHandle _ambientMusic; ///< Sound handle of the currently playing music.

	Common::UString _modelName;      ///< Name of area geometry ("tile") model.
	Graphics::Aurora::Model *_model; ///< The actual area geometry model.

	ObjectList _objects;   ///< List of all objects in the area.
	ObjectMap  _objectMap; ///< Map of all non-static objects in the area.

	/** The currently active (highlighted) object. */
	Engines::Witcher::Object *_activeObject;

	bool _highlightAll; ///< Are we currently highlighting all objects?

	std::list<Events::Event> _eventQueue; ///< The event queue.

	Common::Mutex _mutex; ///< Mutex securing access to the area.


	// Loading helpers

	void clear();

	void loadARE(const Aurora::GFFStruct &are);
	void loadGIT(const Aurora::GFFStruct &git);

	void loadProperties(const Aurora::GFFStruct &props);

	void loadObject(Engines::Witcher::Object &object);
	void loadWaypoints (const Aurora::GFFList &list);
	void loadPlaceables(const Aurora::GFFList &list);
	void loadDoors     (const Aurora::GFFList &list);

	// Model loading/unloading helpers

	void loadModels();
	void unloadModels();

	void loadAreaModel();
	void unloadAreaModel();

	// Highlight / active helpers

	void checkActive(int x = -1, int y = -1);
	void setActive(Engines::Witcher::Object *object);
	Engines::Witcher::Object *getObjectAt(int x, int y);

	void highlightAll(bool enabled);

	void click(int x, int y);
};

} // End of namespace Witcher

} // End of namespace Engines

#endif // ENGINES_WITCHER_AREA_H