/*
** BadCFG - config file reader
*/

#ifndef __BADCFG_H_INCLUDED__
#define __BADCFG_H_INCLUDED__

/*! @module "libbadcfg core"
 *
 * Provides functionality for parsing tree-structured text files.
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef
/* hack to make SlashDOC's C++ parser to see this as a class */
/**
 * BadCFGNode includes information about a single node in the generated tree.
 */
struct BadCFGNode
{
	/** The node's name. This is the name given at the 'left' side of the
	 * configuration line. */
	char			*name;
	/** The node's value. If the node has a value (an assignment given in
	 * the configuration file), this is the value. Else it is NULL. */
	char			*value;
	/** The parent of the node. */
	struct BadCFGNode	*parent;
	/** The node's first child. */
	struct BadCFGNode	*child;
	/** The node's last child. */
	struct BadCFGNode	*lastChild;
	/** The previous node. */
	struct BadCFGNode	*previous;
	/** The next node. */
	struct BadCFGNode	*next;
} BadCFGNode;

/**
 * Loads and parses a BadCFG file. The given file is loaded in memory and passed
 * to the {@link parseBadCFGCode} function in order to generate a tree of
 * {@link BadCFGNode} objects.
 *
 * @param fileName The filename to open.
 * @return The root node of the BadCFGNode tree.
 */
BadCFGNode *loadBadCFGFile(const char *fileName);

/**
 * Parses the given BadCFG code and generates a tree of {@link BadCFGNode}
 * objects. Unless you want to use some other means of loading configuration
 * files (such as directly from an archive), you should use
 * {@link loadBadCFGFile} instead.
 *
 * @param code The BadCFG code as loaded from the file.
 * @return The root node of the BadCFGNode tree.
 */
BadCFGNode *parseBadCFGCode(const char *code);

/**
 * Returns the {@link BadCFGNode} child of the given node that has the given
 * name. This must be a direct child (no searching is performed). The name can
 * consist of several names in a {@code parent.child} fashion. For example, if
 * the root node has a child named {@name info} and that child has a child
 * named {@name title}, then you can get the value of that last child by using
 * the name {@name info.title}.
 *
 * @param root The root (or parent) node to search for the name in.
 * @param name The name of the child or the path to the child as described
 *	above.
 */
BadCFGNode *getBadCFGNode(BadCFGNode *root, const char *name);

/**
 * Returns the value of the given node or a default value if the node wasn't
 * found. The rules about the name are the same as described in the
 * {@link getBadCFGNode} function. In fact, this calls the
 * {@name getBadCFGNode} function and returns it's {@link BadCFGNode.value}
 * field or the value of {@name defaultValue} if the node wasn't found.
 *
 * @param root The root (or parent) node to search for the name in.
 * @param name The name of the child or the path to the child.
 * @param defaultValue The default value to be returned if the child wasn't
 *	found.
 */
const char *getBadCFGValue(BadCFGNode *root, const char *name, const char *defaultValue);

/**
 * Destroys the given node (or tree). This must be used when the
 * {@link BadCFGNode} tree returned from {@link parseBadCFGCode} or
 * {@link loadBadCFGFile} is not needed anymore. You don't need to destroy each
 * node manually; this function will delete the given node, including it's
 * children and grandchildren.
 *
 * @param node The node to destroy.
 */
void destroyBadCFGNode(BadCFGNode *node);

#ifdef __cplusplus
};
#endif

#endif
