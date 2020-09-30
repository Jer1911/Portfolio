def read_file_to_list():
	infile = open('links.txt','r')
	bad_urls = infile.readlines()
	infile.close()
	return bad_urls

def fix_urls(bad_urls):
    good_urls = []
    prefix = "https://REDACTED.photobucket.com/albums/REDACTED/REDACTED/everything/"
    for url in bad_urls:
        filename = url[57:-6]
        good_urls.append(prefix + filename)
    return good_urls


def write_file(good_urls):
    outfile = open('fixed_links.txt','w')
    for url in good_urls:
        outfile.write(url + "\n")
    outfile.close()

def main():
    bad_urls = read_file_to_list()
    good_urls = fix_urls(bad_urls)
    write_file(good_urls)

main()

