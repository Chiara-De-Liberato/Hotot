/***************************************************************************
 *   Copyright (C) 2011~2011 by CSSlayer                                   *
 *   wengxt@gmail.com                                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, version 2 of the License.               *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "common.h"

// KDE
#include <KStatusNotifierItem>
#include <KMenu>
#include <KIcon>

// Hotot
#include "mainwindow.h"
#include "kdetraybackend.h"

KDETrayBackend::KDETrayBackend(MainWindow* parent):
    TrayIconBackend(parent),
    m_mainWindow(parent),
    m_statusNotifierItem(new KStatusNotifierItem("hotot-qt", this))
{
    m_statusNotifierItem->setIconByName("hotot_qt");
    m_statusNotifierItem->setTitle("Hotot");
    m_statusNotifierItem->setToolTipIconByName("hotot_qt");
    m_statusNotifierItem->setStatus(KStatusNotifierItem::Active);
    m_statusNotifierItem->setCategory(KStatusNotifierItem::Communications);
    m_statusNotifierItem->setStandardActionsEnabled(false);
    m_statusNotifierItem->setToolTipTitle(i18n("Hotot"));

    connect(m_statusNotifierItem, SIGNAL(activateRequested(bool, QPoint)), this, SLOT(activate()));
}

void KDETrayBackend::showMessage(QString type, QString title, QString message, QString image)
{
    Q_UNUSED(type)
    Q_UNUSED(image)
    m_statusNotifierItem->setStatus(KStatusNotifierItem::NeedsAttention);
    m_statusNotifierItem->showMessage(title, message, "hotot_qt", 4000);
}

void KDETrayBackend::setContextMenu(QMenu* menu)
{
    KMenu* kmenu = m_statusNotifierItem->contextMenu();
    Q_FOREACH(QAction * action, menu->actions()) {
        kmenu->addAction(action);
    }
}

void KDETrayBackend::activate()
{
    m_mainWindow->triggerVisible();
}

void KDETrayBackend::unreadAlert(QString number)
{
    m_statusNotifierItem->setToolTipSubTitle(i18n("%1 unread Messages").arg(number));
}

#include "kdetraybackend.moc"