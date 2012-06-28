/*
 * Copyright (c) [2009-2012] Novell, Inc.
 *
 * All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, contact Novell, Inc.
 *
 * To contact Novell about this file by physical or electronic mail, you may
 * find current contact information at www.novell.com.
 */

/*
 * File:	QY2Graph.h
 * Author:	Arvin Schnell <aschnell@suse.de>
 */


#ifndef QY2Graph_h
#define QY2Graph_h

#include <graphviz/gvc.h>
#include <string>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPathItem>
#include <QPicture>
#include <QContextMenuEvent>
#include <QMouseEvent>


/**
 * The QY2Graph widget shows a graph layouted by graphviz in a
 * QGraphicsView/QGraphicsScene.
 */
class QY2Graph : public QGraphicsView
{
    Q_OBJECT

public:

    QY2Graph(const std::string& filename, const std::string& layoutAlgorithm, QWidget* parent = 0);

    QY2Graph(graph_t* graph, QWidget* parent = 0);

    virtual ~QY2Graph();

    virtual void renderGraph(const std::string& filename, const std::string& layoutAlgorithm);
    virtual void renderGraph(graph_t* graph);

    void clearGraph();

signals:

    void backgroundContextMenuEvent(QContextMenuEvent* event);
    void nodeContextMenuEvent(QContextMenuEvent* event, const QString& name);
    void nodeDoubleClickEvent(QMouseEvent* event, const QString& name);

protected:

    void keyPressEvent(QKeyEvent* event);
    void wheelEvent(QWheelEvent* event);
    void contextMenuEvent(QContextMenuEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);

private:

    void init();

    void scaleView(qreal scaleFactor);

    QGraphicsScene* scene;

    QRectF graphRect;

    QPointF gToQ(const pointf& p, bool upside_down = true) const;

    QString aggetToQString(void* obj, const char* name, const QString& fallback) const;
    QColor aggetToQColor(void* obj, const char* name, const QColor& fallback) const;
    Qt::PenStyle aggetToQPenStyle(void* obj, const char* name, const Qt::PenStyle fallback) const;

    QPainterPath makeShape(node_t* node) const;
    QPolygonF makeShapeHelper(node_t* node) const;

    QPainterPath makeBezier(const bezier& bezier) const;

    void drawLabel(const textlabel_t* textlabel, QPainter* painter) const;

    void drawArrow(const QLineF& line, const QColor& color, QPainter* painter) const;

};


class QY2Node : public QObject, public QGraphicsPathItem
{
    Q_OBJECT

public:

    QY2Node(const QPainterPath& path, const QPicture& picture, const QString& name);

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

private:

    QPicture picture;

public:

    QString name;

};


class QY2Edge : public QGraphicsPathItem
{

public:

    QY2Edge(const QPainterPath& path, const QPicture& picture);

    QRectF boundingRect() const;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

private:

    QPicture picture;

};


#endif // QY2Graph_h
