/* QtCSG provides Constructive Solid Geometry (CSG) for Qt
 * Copyright Ⓒ 2023 Mathias Hasselmann
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */
#include "qtcsgutils.h"

#include <QLoggingCategory>

namespace QtCSG::Utils {

bool reportError(const QLoggingCategory &category, Error error,
                 const char *message, std::source_location location)
{
    if (Q_LIKELY(error == Error::NoError))
        return false;

    if (category.isWarningEnabled()) {
        auto logger = QMessageLogger{location.file_name(), static_cast<int>(location.line()),
                                     location.function_name(), category.categoryName()};
        logger.warning("%s, the reported error is %s", message, keyName(error));
    }

#ifdef QTCSG_IGNORE_ERRORS
    return false;
#else
    return true;
#endif
}

} // namespace QtCSG::Utils
