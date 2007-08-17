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

#include "world.hpp"
#include "smallmap_image.hpp"
#include "col_map.hpp"
#include "server.hpp"


SmallMapImage::SmallMapImage(Server* s, int width, int height)
  : server(s),
    canvas(width, height),
    update_count(0),
    colmap_serial(0)
{
  update_surface();
}

void
SmallMapImage::update (float delta)
{
  float smallmap_update_time = 1.0f;

  update_count += delta;

  if (update_count > smallmap_update_time)
    {
      update_count = 0.0f;
      ColMap* colmap = server->get_world()->get_colmap();

      if (colmap_serial != colmap->get_serial())
        {
          update_surface();
        }
    }
}

Sprite
SmallMapImage::get_surface ()
{
  if (sur)
    {
      return sur;
    }
  else
    {
      update_surface();
      return sur;
    }
}

void
SmallMapImage::update_surface()
{
  unsigned char* cbuffer;

  ColMap* colmap = server->get_world()->get_colmap();

  colmap_serial = colmap->get_serial();

  canvas.lock();

  cbuffer = static_cast<unsigned char*>(canvas.get_data());

  int cmap_width  = colmap->get_width();
  int cmap_height = colmap->get_height();

  int width  = canvas.get_width();
  int height = canvas.get_height();
  int pitch  = canvas.get_pitch();

  assert(width < cmap_width && height < cmap_height);

  for(int y = 0; y < height; ++y)
    {
      for (int x = 0; x < width; ++x)
	{
          // Index on the smallmap canvas
          int i = y * pitch + 4 * x;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
              const int red   = 3;
              const int green = 2;
              const int blue  = 1;
              const int alpha = 0;
#else
              const int red   = 0;
              const int green = 1;
              const int blue  = 2;
              const int alpha = 3;
#endif 

          switch (colmap->getpixel_fast(x * cmap_width  / width,
                                        y * cmap_height / height))
            {
            case Groundtype::GP_NOTHING:
              cbuffer[i + red]   = 0;
              cbuffer[i + green] = 0;
              cbuffer[i + blue]  = 0;
              cbuffer[i + alpha] = 255;
              break;

            case Groundtype::GP_BRIDGE:
              cbuffer[i + red]   =   0;
              cbuffer[i + green] = 255;
              cbuffer[i + blue]  = 100;
              cbuffer[i + alpha] = 255;
              break;

            case Groundtype::GP_WATER:
            case Groundtype::GP_LAVA:
              cbuffer[i + red]   = 0;
              cbuffer[i + green] = 0;
              cbuffer[i + blue]  = 200;
              cbuffer[i + alpha] = 255;
              break;

#if 0
              // FIXME: temporaty disabled for 0.6.0 release, since all liquids are currently lava
            case Groundtype::GP_LAVA:
              cbuffer[i + 3] = 255; // alpha
              cbuffer[i + 2] = 255; // blue
              cbuffer[i + 1] = 128;   // green
              cbuffer[i + 0] = 128;   // red
              break;
#endif

            case Groundtype::GP_SOLID:
              cbuffer[i + red]   = 100;
              cbuffer[i + green] = 100;
              cbuffer[i + blue]  = 100;
              cbuffer[i + alpha] = 255;
              break;

            default:
              cbuffer[i + red]   = 200;
              cbuffer[i + green] = 200;
              cbuffer[i + blue]  = 200;
              cbuffer[i + alpha] = 255;
              break;
            }
	}
    }
  canvas.unlock();
  sur = Sprite(canvas);
}


/* EOF */
