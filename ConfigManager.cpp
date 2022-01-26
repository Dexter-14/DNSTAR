#include "ConfigManager.hpp"

ConfigManager::ConfigManager()
{
    mResolverPort = -1;
    mResolverIP.clear();
}

ConfigManager::~ConfigManager()
{

}

void Config::parseArgs(int aArgc, char* aArgv[])
{
    for(int i =1; i+1 < aArgc; i = i+2)
    {
        char *lArgFlag = aArgv[i];
        char *lArgValue = aArgv = aArgv[i+1];

        if(!strcmp("-p", lArgFlag))
        {
            mResolverPort = atoi(lArgValue);
        }
        else if(!strcmp("-ip", lArgFlag))
        {
            mResolverIP = lArgValue;
        }
    }

    if(mResolverIP.empty())
    {
        parseResolver(mResolverIP);
    }

    if(mResolverPort == -1)
    {
        mResolverPort = 53;
    }
}

int ConfigManager::getResolverPort() const
{
    return mResolverPort;
}

const std::string & ConfigManager::getResolverIPString() const
{
    return mResolverIP;
}

in_addr_t ConfigManager::getResolverIPInetAddr() const
{
    return inet_addr(getResolverIPString().c_str());
}

void ConfigManager::parseResolver(std::string & aResolverIP)
{
    std::ifstream lFileStream;
    lFileStream.open(RESOLVER_CONF_FILE, std::ios::in);
    if(lFileStream.is_open())
    {
        while(!lFileStream.eof())
        {
            std::string lLine;
            getline(lFileStream, lLine);
            std::vector<std::string> lStrings = StringUtilities::SplitString(lLine, " ");

            if(lStrings.size() >= 2 && lStrings[0] == "nameserver")
            {
                mResolverIP = lStrings[1];
            }
        }
    }
    else
    {
        throw ParseException(RESOLVER_CONF_FILE, "Could not open.");
    }
    lFileStream.close();

    if(mResolverIP.empty())
    {
        throw ParseException("Could not determine nameserver.");
    }
}