/******************************************************************************
 * Copyright (C) 2007  Michael Hofmann <mh21@mh21.de>                         *
 *                                                                            *
 * This program is free software; you can redistribute it and/or modify       *
 * it under the terms of the GNU General Public License as published by       *
 * the Free Software Foundation; either version 3 of the License, or          *
 * (at your option) any later version.                                        *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU General Public License for more details.                               *
 *                                                                            *
 * You should have received a copy of the GNU General Public License along    *
 * with this program; if not, write to the Free Software Foundation, Inc.,    *
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.                *
 ******************************************************************************/

#include "xmlutils.h"

#include <QString>

namespace igotu
{

QString xmlIndent(unsigned depth, unsigned indentSize)
{
    return QString(indentSize * depth, QLatin1Char(' '));
}

QString xmlEscapedText(const QString &text)
{
    QString result = text;
    result.replace(QLatin1String("&"), QLatin1String("&amp;"));
    result.replace(QLatin1String("<"), QLatin1String("&lt;"));
    result.replace(QLatin1String(">"), QLatin1String("&gt;"));
    return result;
}

QString xmlEscapedAttribute(const QString &text)
{
    QString result = xmlEscapedText(text);
    result.replace(QLatin1String("\""), QLatin1String("&quot;"));
    result.prepend(QLatin1String("\""));
    result.append(QLatin1String("\""));
    return result;
}

} // namespace igotu

