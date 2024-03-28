/***************************************************************************
 *   Copyright (C) 2014 by Ilya Kotov                                      *
 *   forkotov02@hotmail.ru                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.         *
 ***************************************************************************/

#ifndef CHANNELCONVERTER_P_H
#define CHANNELCONVERTER_P_H

#include "effect.h"

/*! @internal
 * @author Ilya Kotov <forkotov02@hotmail.ru>
 */
class Q_DECL_EXPORT ChannelConverter : public Effect
{
public:
    ChannelConverter(ChannelMap out_map);
    ~ChannelConverter();
    void configure(quint32 srate, ChannelMap in_map, Qmmp::AudioFormat f);
    void applyEffect(Buffer *b);

private:
    bool m_disabled;
    int m_reorder_array[9];
    unsigned char *m_tmp_buf;
    int m_frame_size;
    int m_channels;
    Qmmp::AudioFormat m_format;
    ChannelMap m_out_map;
};

#endif // CHANNELCONVERTER_P_H
