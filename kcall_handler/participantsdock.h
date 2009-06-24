/*
    Copyright (C) 2009  George Kiagiadakis <kiagiadakis.george@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef PARTICIPANTSDOCK_H
#define PARTICIPANTSDOCK_H

#include <QtGui/QDockWidget>
class GroupMembersModel;

class ParticipantsDock : public QDockWidget
{
    Q_OBJECT
public:
    ParticipantsDock(GroupMembersModel *model, QWidget *parent = 0);
};

#endif