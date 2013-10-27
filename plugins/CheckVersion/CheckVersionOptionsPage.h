/*
Copyright (C) 2006 - 2013 Evan Teran
                          eteran@alum.rit.edu

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

#ifndef OPTIONS_PAGE_20090703_H_
#define OPTIONS_PAGE_20090703_H_

#include <QWidget>

namespace Ui { class CheckVersionOptionsPage; }

class CheckVersionOptionsPage : public QWidget {
	Q_OBJECT;

public:
	CheckVersionOptionsPage(QWidget *parent = 0);
	virtual ~CheckVersionOptionsPage();

public:
	virtual void showEvent(QShowEvent *event);

public Q_SLOTS:
	void on_checkBox_toggled(bool checked);

private:
	Ui::CheckVersionOptionsPage *const ui;
};

#endif
