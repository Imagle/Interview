#include "ini_parser.h"
#include <vector>
#include <fstream>
using namespace std;

namespace qh
{
    namespace {

        template< class _StringVector, 
        class StringType,
        class _DelimType> 
            inline void StringSplit(  
            const StringType& str, 
            const _DelimType& delims, 
            unsigned int maxSplits, 
            _StringVector& ret)
        {
            unsigned int numSplits = 0;

            // Use STL methods
            size_t start, pos;
            start = 0;

            do
            {
                pos = str.find_first_of( delims, start );

                if ( pos == start )
                {
                    ret.push_back(StringType());
                    start = pos + 1;
                }
                else if ( pos == StringType::npos || ( maxSplits && numSplits + 1== maxSplits ) )
                {
                    // Copy the rest of the string
                    ret.push_back(StringType());
                    *(ret.rbegin()) = StringType(str.data() + start, str.size() - start);
                    break;
                }
                else
                {
                    // Copy up to delimiter
                    //ret.push_back( str.substr( start, pos - start ) );
                    ret.push_back(StringType());
                    *(ret.rbegin()) = StringType(str.data() + start, pos - start);
                    start = pos + 1;
                }

                ++numSplits;

            }
            while ( pos != StringType::npos );
        }
    }

    INIParser::INIParser(){
        
    }

    INIParser::~INIParser(){

    }

    //! \brief 解析一个磁盘上的INI文件
    //! \param[in] - const std::string & ini_file_path
    //! \return - bool
    bool INIParser::Parse(const std::string& ini_file_path){
        ifstream file(ini_file_path.c_str());
        if(!file)
            return false;
        file.seekg(0, ios::end);
        size_t len = file.tellg();
        if(len<0)
            return false;
        char* buffer = new char[len+1];
        if(0==buffer)
            return false;
        file.seekg(0,ios::beg);
        file.read(buffer, len);
        buffer[len=file.gcount()] = 0;
        Parse(buffer, len);
        delete[] buffer;
        return true;
    }

    //! \brief 解析一段形如INI格式的内存数据
    //! \param[in] - const char * ini_data
    //! \param[in] - size_t ini_data
    //! \param[in] - const std::string & line_seperator
    //! \param[in] - const std::string & key_value_seperator
    //! \return - bool
    bool INIParser::Parse(const char* ini_data, size_t ini_data_len, const std::string& line_seperator, const std::string& key_value_seperator ){
        vector<string> v;
        StringSplit(std::string(ini_data), line_seperator, ini_data_len, v);
        int i = 0;
        //printf("after stringsplit\n");
        std::string section = "default";
        for(; i<v.size(); i++){
            std::string work_str = v[i]; 
            int pos = work_str.find(key_value_seperator);
            if( pos == std::string::npos ){
                section = work_str.substr(work_str.find('[')+1, work_str.find(']')-1);
                continue;
            }
            std::string key = work_str.substr(0, pos);
            std::string value = work_str.substr(pos+1);
            sectionmap[section][key] = value;
        }
        v.clear();
        //printf("return from paser memory\n");
        return true;
    }

    //! \brief 从默认section中查找某个key，并返回找到的value。如果找不到，返回一个空串
    //! \param[in] - const std::string & key
    //! \param[in] - bool * found - 输出参数，true表明找到这个key
    //! \return - const std::string& - 返回的具体key对应的value
    const std::string& INIParser::Get(const std::string& key, bool* found){
        std::string section = "default";
        //printf("get from defalut section\n");
        return Get(section, key, found);
    }

    const std::string& INIParser::Get(const std::string& section, const std::string& key, bool* found){
        if(key.empty())
            return key;
        SectionMap::iterator it;
        it = sectionmap.find(section);
        if(found != NULL)
            *found = false;
        //printf("get from named section\n");
        if(it == sectionmap.end())
            return "";
        KeyMap::iterator keyit;
        keyit = it->second.find(key);
        if(keyit == it->second.end())
            return "";
        if(found != NULL)
            *found = true;
        return keyit->second;
    }

}
