#include <deque>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include <stack>

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
	std::vector<TreeNode*> traversedNodes;
	std::stack<TreeNode*> treeStack;

	while(root != NULL){
		root = root->leftChild.get();
	}

	
	// TODO 6.3a: Traverse the tree depth-first
}

void breadthFirstTraversal(const TreeNode* root)
{
	// TODO 6.3b: Traverse the tree breadth-first
}

struct Point
{
	int x;
	int y;
};

void writeSVGNode(std::ofstream& stream, int id, const Point& p)
{
	// TODO 6.3c: Draw a circle at (p.x, p.y) and write the ID of the node inside of it
}

void writeSVGEdge(std::ofstream& stream, const Point& p1, const Point& p2)
{
	// TODO 6.3c: Draw a line from (p1.x, p1.x) to (p2.x, p2.y)
}

void writeSVG(const TreeNode* root, const std::string& filename)
{
	// TODO 6.3a: Write a valid svg file with the given filename which shows the given tree
}

int main()
{
	const auto root1 = newTree({ 6, 2, 1, 4, 3, 5, 7, 9, 8 });
	const auto root2 = newTree({ 5, 9, 7, 6, 2, 1, 4, 3, 8 });

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

	return 0;
}
