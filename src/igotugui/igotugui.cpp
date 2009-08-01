/******************************************************************************
 * Copyright (C) 2009  Michael Hofmann <mh21@piware.de>                       *
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

#include "igotu/messages.h"
#include "igotu/optionutils.h"

#include "iconstorage.h"
#include "mainwindow.h"

#include <boost/program_options.hpp>

#include <QApplication>
#include <QFileInfo>
#include <QLocale>

#include <iostream>

using namespace igotu;

namespace po = boost::program_options;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName(QLatin1String("igotugui"));
    app.setOrganizationName(QLatin1String("mh21.de"));
    app.setOrganizationDomain(QLatin1String("mh21.de"));
    app.setWindowIcon(IconStorage::get(IconStorage::GuiIcon));
#if defined(Q_OS_MACX) && QT_VERSION >= 0x040400
    app.setAttribute(Qt::AA_DontShowIconsInMenus);
#endif

    // Command line parsing (uses C++ output)

    po::variables_map variables;

    po::options_description options("Options");
    options.add_options()
        ("help", "output this help and exit")
        ("version", "output version information and exit")

        ("verbose,v",
         "increase the amount of informative messages")
    ;

    try {
        po::store(po::command_line_parser(arguments())
                .options(options).run(), variables);
        po::notify(variables);

        if (variables.count("version")) {
            Messages::textOutput(Common::tr(
                   "Igotu2gpx %1\n\n"
                   "Shows the configuration and decodes the stored tracks and waypoints\n"
                   "of a MobileAction i-gotU USB GPS travel logger.\n\n"
                   "This program is licensed to you under the terms of the GNU General\n"
                   "Public License. See the file LICENSE that came with this software\n"
                   "for further details.\n\n"
                   "Copyright (C) 2009 Michael Hofmann.\n\n"
                   "The program is provided AS IS with NO WARRANTY OF ANY KIND,\n"
                   "INCLUDING THE WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR\n"
                   "A PARTICULAR PURPOSE.").arg(QLatin1String(IGOTU_VERSION_STR)));
            return 0;
        }
        if (variables.count("help")) {
            Messages::textOutput(Common::tr("Usage:"));
            Messages::textOutput(MainWindow::tr("%1 [OPTIONS...]")
                .arg(QFileInfo(app.applicationFilePath()).fileName()));
            std::cout << options << "\n";
            return 1;
        }
    } catch (const std::exception &e) {
        Messages::errorMessage(Common::tr("Unable to parse command line: %1")
                    .arg(QString::fromLocal8Bit(e.what())));
        return 2;
    }

    Messages::setVerbose(variables.count("verbose"));

    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
