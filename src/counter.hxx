//  $Id: counter.hxx,v 1.4 2002/08/23 15:49:48 torangan Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 1999 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_PINGUS_COUNTER_HXX
#define HEADER_PINGUS_COUNTER_HXX

#include "pingus.hxx"

class Counter
{
public:
  enum CounterType { loop, once, ping_pong, ping_pong_once };

private:
  int s;
  int count;
  int add;
  CounterType type;

public:
  Counter(int s);
  Counter();
  Counter(const Counter&);
  virtual ~Counter();

  Counter& operator=(const Counter&);
  int  inc();
  int  operator++();
  int  operator--();
  int  operator=(int i);
  int  get_value() const;
  int  size() const;
  int  set_count(int i);
  int  set_size(int s);
  void set_type(CounterType);
  operator int() const { return count; };
};

#endif

/* EOF */