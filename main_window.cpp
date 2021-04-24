/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "main_window.h"
#include "athletes_widget.h"
#include "relay_widget.h"
#include "project.h"

main_window::main_window()
{
  m_project = new project ();
  QWidget *central_widget = new QWidget (this);
  auto *main_layout = new QVBoxLayout;
//  main_layout->addWidget (new athletes_widget (*m_project, central_widget));
  main_layout->addWidget (new relay_widget (*m_project, central_widget));
  central_widget->setLayout (main_layout);
  setCentralWidget (central_widget);

  create_menu_bar ();
}

void main_window::create_menu_bar ()
{
//    QAction *quitAction = new QAction(tr("&Quit"), this);
//    QAction *aboutAction = new QAction(tr("&About"), this);
//    QAction *aboutQtAction = new QAction(tr("&About Qt"), this);
//
//    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
//    fileMenu->addAction(quitAction);
//
//    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
//    helpMenu->addAction(aboutAction);
//    helpMenu->addAction(aboutQtAction);
//
//    connect(quitAction, &QAction::triggered, this, &Window::close);
//    connect(aboutAction, &QAction::triggered, this, &Window::about);
//    connect(aboutQtAction, &QAction::triggered, qApp, &QApplication::aboutQt);
}

void main_window::about ()
{}
