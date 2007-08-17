//  $Id$
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#ifndef HEADER_PINGUS_INPUT_EVENT_HXX
#define HEADER_PINGUS_INPUT_EVENT_HXX

#error "Don't used this the moment, its underdevelopment and not compilable"

#include "pingus.hpp"
#include "vector.hpp"


/** This will need some^H^H^H^H a lot of work */
typedef enum {
  /** Pointer Events (pos contains the move-delta) */
  MOUSE_MOVE,

  /** The scroll controll has been move, in theory this could be a
      second mouse, an second analog stick or a combination of button
      press and cursor movement */
  SCROLL_MOVE,

  /** The button that turns the MOUSE_MOVE into a SCROLL_MOVE */
  SCROLL_MODIFIER,

  /*** Generic button events (pos contains position) */
  PRIMARY_BUTTON_PRESSED,
  SECONDARY_BUTTON_PRESSED,

  /** Escape is pressed */
  ESCAPE_TRIGGERED,

  /** 'p' or 'Pause' got pressed */
  PAUSE_PRESSED,
  FASTFORWARD_TRIGGERED,

  /** Buttons for switching to the next/previous Action */
  ACTION_UP,
  ACTION_DOWN,

  /** Action selected, Most likly one of the F1-F?? buttons is
      pressed, this could also be a combination of shift-button or
      something else */
  ACTION_SELECTED

} InputEventType;


class InputEvent
{
public:
  /** Position or movement */
  Vector pos;

  /** integer data */
  int data;

  /** The type of event */
  EventType type;

  /** The 'owner' or player of this event */
  int owner;
};


#endif

/* EOF */
