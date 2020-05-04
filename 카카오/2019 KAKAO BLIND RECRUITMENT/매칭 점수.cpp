#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
int solution(string word, vector<string> pages) {
    int answer = 0;
    vector<pair<string, double>> pageurl;
    map<string, double> score;
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    for (int i = 0; i < pages.size(); i++) {
        string data = pages[i];
        transform(data.begin(), data.end(), data.begin(), ::tolower);
        //url 찾기
        string url;
        int idx = data.find("<meta property=\"og:url\" content=\"https://") + 41;
        while (data[idx] != '"')
            url += data[idx++];
        pageurl.push_back({ url, 0 });
        //단어 찾기
        double wordCnt = 0, linkcnt = 0;
        idx += data.substr(idx).find("<body>") + 6;
        auto bodyend = idx + data.substr(idx).find("/body");
        int wordIdx = idx;
        while (wordIdx < bodyend) {
            int tmp = wordIdx + data.substr(wordIdx).find(word);
            if (tmp + 1 == wordIdx) break;
            wordIdx = tmp + word.length();
            int checkalphabet = 0;
            if ('a' <= data[tmp - 1] && data[tmp - 1] <= 'z')
                checkalphabet++;
            while ('a' <= data[wordIdx] && data[wordIdx] <= 'z') {
                checkalphabet++;
                wordIdx++;
            }
            if (checkalphabet) continue;
            wordCnt++;
        }
        //외부 링크 찾기
        vector<string> exlink;
        int linkIdx = idx;
        while (linkIdx < bodyend) {
            int tmp = linkIdx + data.substr(linkIdx).find("<a href=\"https://");
            if (tmp + 1 == linkIdx) break;
            string link;
            linkIdx = tmp + 17;
            while (data[linkIdx] != '"')
                link += data[linkIdx++];
            exlink.push_back(link);
            linkcnt++;
        }
        score[url] += wordCnt;
        for (int i = 0; i < linkcnt; i++)
            score[exlink[i]] += wordCnt / linkcnt;
    }
    for (auto it = score.begin(); it != score.end(); it++) {
        for (int i = 0; i < pageurl.size(); i++) {
            if (pageurl[i].first.compare(it->first) == 0) {
                pageurl[i].second = it->second;
                break;;
            }
        }
    }
    double maxv = 0;
    for (int i = 0; i < pageurl.size(); i++)
        if (maxv < pageurl[i].second) {
            maxv = pageurl[i].second;
            answer = i;
        }
    return answer;
}
int main()
{
    string word = "aba";
    vector<string> pages = { "<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://a.com\"/>\n</head>  \n<body>\nhi hello \n<a href=\"https://d.com\"> Link to b </a></body>\n</html>", "<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://b.com\"/>\n</head>  \n<body>\nabab abababa aba@aba aba hi pi lo Hi hi hI vi, \n<a href=\"https://a.com\"> Link to a </a><a href=\"https://d.com\"> Link to a </a>\n</body>\n</html>", "<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://c.com\"/>\n</head>  \n<body>\nhi HI Hi hi hi HI HI hi hi \n<a href=\"https://a.com\"> Link to a </a>\n<a href=\"https://E.com\"> Link to a </a><a href=\"https://F.com\"> Link to a </a>\n\n</body>\n</html>" };
    cout << solution(word, pages);
}