//  $Id$
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2005 Ingo Ruhnke <grumbel@gmx.de>
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

#include <iostream>
#include "resource.hpp"
#include "system.hpp"
#include "collision_mask.hpp"

CollisionMask::CollisionMask()
  : buffer(0)
{
}

CollisionMask::CollisionMask(const std::string& name)
{
  ResDescriptor res_desc(name);
  init(res_desc);
}

CollisionMask::CollisionMask(const ResDescriptor& res_desc)
  : buffer(0)
{
  init(res_desc);
}

void
CollisionMask::init(const ResDescriptor& res_desc)
{
  //std::cout << "CollisionMask: " << name << std::endl;
  surface = Resource::load_surface(res_desc);
  //Surface cmap = surface; // Resource::load_surface(System::cut_ext(name) + "_cmap");

  int pitch = surface.get_pitch();
  width  = surface.get_width();
  height = surface.get_height();
  
  buffer = new uint8_t[width * height];

  SDL_Surface* sdl_surface = surface.get_surface();
  SDL_LockSurface(sdl_surface);

  if (sdl_surface->format->palette)
    {
      uint8_t* source = static_cast<uint8_t*>(sdl_surface->pixels);
      if (sdl_surface->flags & SDL_SRCCOLORKEY)
        { // surface with transparent areas
          for(int y = 0; y < height; ++y)
            for(int x = 0; x < width; ++x)
              {
                if (source[y*pitch + x] == sdl_surface->format->colorkey)
                  buffer[y*width + x] = 0;
                else
                  buffer[y*width + x] = 1;
              }
        }
      else
        { // completly opaque surface
          memset(buffer, 1, width*height);
        }
    }
  else
    {
      printf("CollisionMask: unsupported image format:\n" 
             "  File: %s\n"
             "  BitsPerPixel: %d\n"
             "  BytesPerPixel: %d\n"
             "  rmask: 0x%08x\n"
             "  gmask: 0x%08x\n"
             "  bmask: 0x%08x\n"
             "  amask: 0x%08x\n",
             res_desc.res_name.c_str(),
             int(sdl_surface->format->BitsPerPixel),
             int(sdl_surface->format->BytesPerPixel),
             (unsigned int)sdl_surface->format->Rmask,
             (unsigned int)sdl_surface->format->Gmask,
             (unsigned int)sdl_surface->format->Bmask,
             (unsigned int)sdl_surface->format->Amask);
    }

  SDL_UnlockSurface(sdl_surface);
}

CollisionMask::~CollisionMask()
{
  delete[] buffer;
}  

int
CollisionMask::get_width() const
{
  return width;
}

int
CollisionMask::get_height() const
{
  return height;
}

Surface
CollisionMask::get_surface() const
{
  return surface;
}

uint8_t*
CollisionMask::get_data() const
{
  return buffer;
}

/* EOF */
