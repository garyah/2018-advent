#include <map>
#include <set>
#include <string>

namespace Advent2018
{
    class StepSorter
    {
    public:
        StepSorter()
        {
        }

        void addStepDependency(const char *input)
        {
			char parentStep = 0;
			char childStep = 0;
            (void)sscanf_s(input, "Step %1c must be finished before step %1c can begin.", &parentStep, 1, &childStep, 1);
			m_childParentList[childStep].insert(parentStep);
			m_parentChildList[parentStep].insert(childStep);
			if (m_childParentList.find(parentStep) == m_childParentList.end())
			{
				NodeSetType emptySet;
				m_childParentList[parentStep] = emptySet;
			}
		}

        const char *getStepList()
        {
			m_stepList.empty();
			while (m_childParentList.size())
			{
				for (auto it = m_childParentList.begin(); it != m_childParentList.end(); ++it)
				{
					auto parents = it->second;
					if (parents.size() == 0)
					{
						auto rootNode = it->first;
						auto children = m_parentChildList[rootNode];
						for (auto it2 = children.begin(); it2 != children.end(); ++it2)
						{
							m_childParentList[*it2].erase(rootNode);
						}
						m_childParentList.erase(rootNode);
						m_stepList += rootNode;
						break;
					}
				}
			}
            return m_stepList.c_str();
        }

		char pullNextWork()
		{
			for (auto it = m_childParentList.begin(); it != m_childParentList.end(); ++it)
			{
				auto parents = it->second;
				if (parents.size() == 0)
				{
					auto rootNode = it->first;
					m_childParentList.erase(rootNode);
					return rootNode;
				}
			}
			return 0;
		}

		const char addedTime = 60;
		bool assignWork(size_t w)
		{
			auto nextWork = pullNextWork();
			workers[w].workNode = nextWork;
			workers[w].timeLeft = nextWork ? (nextWork - 'A' + 1 + addedTime) : 0;
			return (nextWork != 0);
		}

		void assignWorkToAll()
		{
			for (size_t w = 0; w < _countof(workers); ++w)
			{
				(void)assignWork(w);
			}
		}

		bool assignWorkToAllAvailable()
		{
			bool workLeft = false;
			for (size_t w = 0; w < _countof(workers); ++w)
			{
				if (workers[w].workNode == 0) workLeft |= assignWork(w);
			}
			return workLeft;
		}

		bool decrementWork()
		{
			bool workLeft = false;
			for (size_t w = 0; w < _countof(workers); ++w)
			{
				auto workNode = workers[w].workNode;
				if (workNode && workers[w].timeLeft)
				{
					--(workers[w].timeLeft);
					if (workers[w].timeLeft == 0)
					{
						auto children = m_parentChildList[workNode];
						for (auto it2 = children.begin(); it2 != children.end(); ++it2)
						{
							m_childParentList[*it2].erase(workNode);
						}
						workers[w].workNode = 0;
					}
					else workLeft = true;
				}
			}
			return workLeft;
		}

		void logWorkerStatus()
		{
			(void)printf("%03u:  ", m_timeSpent);
			for (size_t w = 0; w < _countof(workers); ++w)
			{
				(void)printf("(%c, %03u)  ", workers[w].workNode ? workers[w].workNode : '.', workers[w].timeLeft);
			}
			(void)printf("\n");
		}

		unsigned getParallelTimeSpent()
		{
			assignWorkToAll();
			m_timeSpent = 0;

			bool workLeft;
			do
			{
				workLeft = false;
				logWorkerStatus();
				workLeft |= decrementWork();
				workLeft |= assignWorkToAllAvailable();
				++m_timeSpent;
			} while (workLeft);

			return m_timeSpent;
		}

    private:
        typedef std::set<char> NodeSetType;
		typedef std::map<char, NodeSetType> NodeMapType;
		typedef struct
		{
			char workNode;
			unsigned timeLeft;
		} WorkItem;
		WorkItem workers[5];

		NodeMapType m_childParentList;
		NodeMapType m_parentChildList;
		std::string m_stepList;
		unsigned m_timeSpent;
	};
}
