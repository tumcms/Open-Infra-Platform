/*
    This file is part of TUM Open Infra Platform Early Binding EXPRESS
    Generator, a simple early binding generator for EXPRESS.
    Copyright (c) 2016-2017 Technical University of Munich
    Chair of Computational Modeling and Simulation.

    TUM Open Infra Platform Early Binding EXPRESS Generator is free
    software; you can redistribute it and/or modify it under the terms
    of the GNU General Public License Version 3 as published by the Free
    Software Foundation.

    TUM Open Infra Platform Early Binding EXPRESS Generator is
    distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "OpenInfraPlatform/ExpressBinding/namespace.h"
#include <string>
#include <vector>
#include <memory>

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDING_BEGIN

class Node;
class RuleLabelIdentifier;
class SchemaDecl;
class DomainRule;
class DomainRules;
class WhereClause;

class NodeVisitor {
public:
	virtual void visit(Node *node) = 0;
};

class GeneratCppDomainRule : public NodeVisitor {
public:
	virtual void visit(Node *node) {

	}
};

class Node {
public:
	virtual ~Node() {
	}
	virtual void accept(NodeVisitor *vistor) {
		vistor->visit(this);
	}
};

class WhereClause : public Node {
public:
	WhereClause(DomainRules* dr) : domain_rules_(dr) {

	}

	DomainRules* domain_rules_;

	virtual void accept(NodeVisitor *vistor) override {
		vistor->visit(this);
	}
};

class DomainRules : public Node {
public:
	std::vector<std::shared_ptr<DomainRule>> domain_rules_;

	void addDomainRule(std::shared_ptr<DomainRule> dr) {
		domain_rules_.push_back(dr);
	}

	virtual void accept(NodeVisitor *vistor) override {
		vistor->visit(this);
	}
};

class SchemaDecl : public Node {
public:
	virtual void accept(NodeVisitor *vistor) override;
};

class RuleLabelIdentifier : public Node {
public:
	std::string name;
	RuleLabelIdentifier(const std::string &name);

	virtual void accept(NodeVisitor *vistor);
};

class Expression : public Node {
public:
	virtual void accept(NodeVisitor *vistor) {
		vistor->visit(this);
	}
};

class BuiltInConstant : public Expression {
public:
	virtual void accept(NodeVisitor *vistor) {
		vistor->visit(this);
	}
};

class Self : public BuiltInConstant {
public:
	virtual void accept(NodeVisitor *vistor) {
		vistor->visit(this);
	}
};

class DomainRule : public Node {
public:
	RuleLabelIdentifier * rule_label_id_;
	Expression* expression_;

	DomainRule(RuleLabelIdentifier* rule_label_id, Expression* expression) :
		rule_label_id_(rule_label_id),
		expression_(expression) {

	}

	virtual void accept(NodeVisitor *vistor) {
		vistor->visit(this);
	}
};

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDING_END

EMBED_INTO_OIP_NAMESPACE(Node);
EMBED_INTO_OIP_NAMESPACE(RuleLabelIdentifier);