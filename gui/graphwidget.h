#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>
#include <QPointer>
#include <QKeyEvent>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QTime>

#include "Quadtree.h"
#include "ForceLayout.h"

#include "node.h"
#include "edge.h"
#include <string>

using namespace std;

class GNode;
class GEdge;

class MyScene : public QGraphicsScene
{
    Q_OBJECT

	public:
	MyScene(QObject * parent = 0): QGraphicsScene(parent) {};
	
	protected:
	void mouseReleaseEvent ( QGraphicsSceneMouseEvent * mouseEvent );
	void mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent );

	signals:
	void zoomArea(QRectF);

	private:
		QPointF down;
		QPointF up;
};


class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GraphWidget();
	~GraphWidget();

	void clear();
    void itemMoved();
    GEdge* addGEdge(GNode* a, GNode* b, string id, void* nodeStates);
    GNode* addGNode(int id);
    GNode* locateGNode(int id);
    void removeGNode(GNode*);
	GEdge* findGEdge(GNode* n1, GNode* n2);

	enum  LayoutAlgorithm { FMMM=1, Circular=2, Balloon=3 };
	LayoutAlgorithm getLayoutAlgorithm() { return _layoutAlgorithm; }

    QVector<GNode*> getGNodes() {return nodelist; }
    int getNumNodes() { return nodelist.size(); }

public slots:
	void resetZoom();
    void zoomIn() { scale(1.2, 1.2); }
    void zoomOut() { scale(1 / 1.2, 1 / 1.2); }
	void zoomArea(QRectF sceneArea) { fitInView(sceneArea,Qt::KeepAspectRatio); }

	void  setLayoutAlgorithm(LayoutAlgorithm x) { _layoutAlgorithm = x; }

	void dump();
    void randomLayout();
    void forceLayout(int iterations);
    void newLayout();
    void clearLayout();
	void removeSelectedGNodes();
    void animateNetwork();
    void setNodeStates(vector< vector<int> > states) { nodeStates = states; _animationTime=0; }
    void clearNodeStates(){ nodeStates.clear(); }
    void recenterItems();

protected:
	void updateSceneRect();
	void keyPressEvent(QKeyEvent *event);

    void scaleView(qreal scaleFactor);
    QVector<GNode*> nodelist;
    void resizeEvent(QResizeEvent*);

private:
	//graph layout
	LayoutAlgorithm	  _layoutAlgorithm;

    //QTreeWidget* layoutTree;
    //QHash<GNode*, QTreeWidgetItem*>layoutMap;
    void timerEvent(QTimerEvent*);

    bool  _updateLayout;
    unsigned int _animationTime;
    int   _timerID;

    vector< vector<int> > nodeStates;

};

#endif
