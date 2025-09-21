# QtNodeItems

A project that creates a workspace where you can create and connect nodes# QtNodeItems

A lightweight and efficient node-based workspace framework for Qt applications.

## Overview

QtNodeItems provides a simple yet powerful framework for creating node-based interfaces in Qt applications. With minimal setup and integration, you can create interactive environments where users can create, connect, and manipulate nodes visually.

![Example Usage](./docs/example.gif)

## Features

- 🚀 **Lightweight**: Minimal dependencies and easy integration
- 🎨 **Customizable**: Flexible node and connection styling
- 🛠️ **Designer Support**: Compatible with Qt Designer for rapid UI development
- 📦 **Header-Only**: Simply include the necessary headers to get started

## Installation

### Method 1: Manual Integration

1. Clone the QtNodeItems repository
2. Add the source files to your project
3. Include the necessary headers in your application:

```cpp
#include "nodeLib/nodeitem.h"  // For creating nodes
#include "nodeLib/nodefield.h" // For display and interaction
```

### Method 2: Using Qt Designer

1. Add a `QGraphicsView` widget to your form in Qt Designer
2. Right-click on the widget and select "Promote to..."
3. In the dialog:
   - **Promoted class name**: `NodeField`
   - **Header file**: `nodefield.h`
4. Click "Add" and then "Promote"

## Quick Start

```cpp
#include "nodeLib/nodeitem.h"
#include "nodeLib/nodefield.h"

// Create a node field
NodeField *nodeField = new NodeField(parent);
QGraphicsScene *scene = QGraphicsScene(nodeField->rect());
nodeField->setScene(scene);
 
// Create nodes
NodeItem *node1 = new NodeItem();
NodeItem *node2 = new NodeItem();
NodeItem *node3 = new NodeItem();

// Add nodes to the field
nodeField->addNode(node1);
nodeField->addNode(node2);
nodeField->addNode(node3);

```

## API Reference

### NodeItem

The main node class that represents individual nodes in the workspace.

**Key Methods:**
- `setNodeId(QString newNodeId)`: Sets the node shadow id
- `setText(QString newText`:  Sets the node title
- `setBrush(QBrush newBrush)`: Sets background color 


### NodeField

The graphics view that contains and manages all nodes and connections.

**Key Methods:**
- `addNode(NodeItem *node)`: Adds a node to the field

## Examples

Check the `mainwindow.cpp` file for implementation examples showing different use cases and customization options.


## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.


## Authors

- [Kortepk](https://github.com/Kortepk) - Initial work
