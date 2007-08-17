//  $Id: solid_color_background.cxx,v 1.4 2002/12/05 20:38:10 torangan Exp $
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

#include <ClanLib/Display/Display/display.h>
#include "../gui/graphic_context.hxx"
#include "../worldobjsdata/solid_color_background_data.hxx"
#include "solid_color_background.hxx"

namespace WorldObjs {

SolidColorBackground::SolidColorBackground (const WorldObjsData::SolidColorBackgroundData& data_)
  : data(new WorldObjsData::SolidColorBackgroundData(data_))
{
}

SolidColorBackground::~SolidColorBackground ()
{
  delete data;
}

void
SolidColorBackground::draw (GraphicContext& gc)
{
  gc.clear(data->color);
}

} // namespace WorldObjs

/* EOF */

