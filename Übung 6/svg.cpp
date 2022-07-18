#include <deque>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <cmath>

struct TreeNode
{
	int id = -1;
	std::unique_ptr<TreeNode> leftChild; // use unique_ptr to automatically destroy the object at end
	std::unique_ptr<TreeNode> rightChild;
	TreeNode* parent = nullptr; // only reference to another unique_ptr, so we don't need a smart pointer here
								// (std::weak_ptr doesn't work with std::unique_ptr)
};

void insertValueToTree(TreeNode* node, int id)
{
	TreeNode* parentNode = nullptr;
	while (node != nullptr)
	{
		parentNode = node;
		if (id <= node->id)
		{
			node = node->leftChild.get();
		}
		else
		{
			node = node->rightChild.get();
		}
	}

	auto newNode = std::make_unique<TreeNode>();
	newNode->id = id;
	newNode->parent = parentNode;
	if (parentNode != nullptr)
	{
		if (id <= parentNode->id)
		{
			parentNode->leftChild = std::move(newNode);
		}
		else
		{
			parentNode->rightChild = std::move(newNode);
		}
	}
}

std::unique_ptr<TreeNode> newTree(const std::vector<int>& ids)
{
	auto rootNode = std::make_unique<TreeNode>();
	rootNode->id = ids[0];
	for (size_t i = 1; i < ids.size(); ++i)
	{
		insertValueToTree(rootNode.get(), ids[i]);
	}

	return rootNode;
}

void depthFirstTraversal(const TreeNode* root)
{
	std::vector<int> traversedNodes;

	while(true){
		//std::cout << "loopstart\n";
		if(!(std::count(traversedNodes.begin(),traversedNodes.end(),root->id))){
			traversedNodes.push_back(root->id);
			std::cout<<root->id<<" , ";
			//std::cout<<"added\n";
		}
		if(root->leftChild &&!(std::count(traversedNodes.begin(),traversedNodes.end(),root->leftChild.get()->id))){
			root = root->leftChild.get();
		}
		else if(root->rightChild &&!(std::count(traversedNodes.begin(),traversedNodes.end(),root->rightChild.get()->id))){
			root = root->rightChild.get();
		}
		else if(root->parent){
			root = root->parent;
		}
		else{
			break;
		}
	}
	
	// TODO 6.3a: Traverse the tree depth-first
}

void breadthFirstTraversal(const TreeNode* root)
{
	// TODO 6.3b: Traverse the tree breadth-first
	std::queue<TreeNode*> nodeQueue;
	nodeQueue.push(const_cast<TreeNode*>(root));
	while(!nodeQueue.empty()){
		if(nodeQueue.front()->leftChild.get()){
			nodeQueue.push(nodeQueue.front()->leftChild.get());
		}
		if(nodeQueue.front()->rightChild.get()){
			nodeQueue.push(nodeQueue.front()->rightChild.get());
		}
		std::cout<<nodeQueue.front()->id<<" , ";
		nodeQueue.pop();
	}
	std::cout << "\n";
}

struct Point
{
	int x;
	int y;
};

int findDepth(const TreeNode* root){
	std::vector<int> traversedNodes;
	int curr_depth = 0;
	int max_depth = 0;

	while(true){
		if(!(std::count(traversedNodes.begin(),traversedNodes.end(),root->id))){
			traversedNodes.push_back(root->id);
		}
		if(root->leftChild &&!(std::count(traversedNodes.begin(),traversedNodes.end(),root->leftChild.get()->id))){
			root = root->leftChild.get();
			curr_depth++;
		}
		else if(root->rightChild &&!(std::count(traversedNodes.begin(),traversedNodes.end(),root->rightChild.get()->id))){
			root = root->rightChild.get();
			curr_depth++;
		}
		else if(root->parent){
			root = root->parent;
			curr_depth--;
		}
		else{
			break;
		}
		if(curr_depth > max_depth) max_depth = curr_depth;
	}
	std::cout << max_depth << "\n";
	return max_depth;
}

void writeSVGNode(std::ofstream& stream, int id, const Point& p)
{
	// TODO 6.3c: Draw a circle at (p.x, p.y) and write the ID of the node inside of it
	int x, y;
	x = p.x * 20;
	y = p.y * 60 + 10;
	stream << "<circle cx=\"" << x << "\" cy=\"" << y << "\" r=\"10\" style=\"fill:white;stroke:black;stroke-width:1\" />\n";
}

void writeSVGEdge(std::ofstream& stream, const Point& p1, const Point& p2)
{
	// TODO 6.3c: Draw a line from (p1.x, p1.x) to (p2.x, p2.y)
}

void writeSVG(const TreeNode* root, const std::string& filename)
{
	// TODO 6.3a: Write a valid svg file with the given filename which shows the given tree
	int depth = findDepth(root);
	int radius = 10;
	int pWidth = pow(2,depth) * 2 * (radius+5);
	int pHeight = 6*radius * (depth+1);

	std::ofstream svgFile;
	svgFile.open(filename);
	svgFile << "<svg version=\"1.0\" xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 "<< pWidth << " " << pHeight << "\" > \n";
	svgFile << "<title>Binary-Tree</title> \n <defs> \n <style type=\"text/css\"> \n </style> \n </defs> \n";

	// ---------- Tiefensuche ------------

	std::vector<int> traversedNodes;
	int curr_depth = 0;
	int curr_width = pow(2,depth);
	Point p;
	while(true){
		if(!(std::count(traversedNodes.begin(),traversedNodes.end(),root->id))){
			traversedNodes.push_back(root->id);
		}
		if(root->leftChild &&!(std::count(traversedNodes.begin(),traversedNodes.end(),root->leftChild.get()->id))){
			root = root->leftChild.get();
			curr_depth++;
			curr_width -= pow(2, (depth - curr_depth));
			p.x = curr_width;
			p.y = curr_depth;
			writeSVGNode(svgFile, root->id, p);
		}
		else if(root->rightChild &&!(std::count(traversedNodes.begin(),traversedNodes.end(),root->rightChild.get()->id))){
			root = root->rightChild.get();
			curr_depth++;
			curr_width += pow(2, (depth - curr_depth));
			p.x = curr_width;
			p.y = curr_depth;
			writeSVGNode(svgFile, root->id, p);
		}
		else if(root->parent){
			root = root->parent;
			int lol = curr_width;
			while (lol % 2 == 0)
			{
				lol /= 2;
			}
			if (lol % 4 == 1)
			{
				curr_width += pow(2, (depth - curr_depth));
			} else {
				curr_width -= pow(2, (depth - curr_depth));
			}
			curr_depth--;
		}
		else{
			break;
		}
	}

	// -----------------------------------

	svgFile << "</svg>";
}

int main()
{
	const auto root1 = newTree({ 6, 2, 1, 4, 3, 5, 7, 9, 8 });
	const auto root2 = newTree({ 5, 9, 7, 6, 2, 1, 4, 3, 8 });
/*
	std::cout << "TreeNode 1:" << std::endl;
	std::cout << "Breadth-first: ";
	breadthFirstTraversal(root1.get());
	std::cout << std::endl;

	std::cout << "Depth-first:   ";
	depthFirstTraversal(root1.get());
	std::cout << std::endl << std::endl;

	std::cout << "TreeNode 2:" << std::endl;
	std::cout << "Breadth-first: ";
	breadthFirstTraversal(root2.get());
	std::cout << std::endl;

	std::cout << "Depth-first:   ";
	depthFirstTraversal(root2.get());
	std::cout << std::endl;

	writeSVG(root1.get(), "tree1.svg");
	writeSVG(root2.get(), "tree2.svg");
*/
	std::cout << "Depth-first:   ";
	depthFirstTraversal(root1.get());
	std::cout << "\nBreadth-first: ";
	breadthFirstTraversal(root1.get());
	std::cout << std::endl << std::endl;

	writeSVG(root1.get(),"tree.svg");
	return 0;
}
