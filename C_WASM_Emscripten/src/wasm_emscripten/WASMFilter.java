package web01;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

import javax.servlet.Filter;
import javax.servlet.FilterChain;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.annotation.WebFilter;
import javax.servlet.http.HttpServletRequest;

/*
或者web.xml增加配置
<mime-mapping>
	<extension>wasm</extension>
	<mime-type>application/wasm</mime-type>
</mime-mapping>
 */

//asyncSupported=true
//JS中使用fetch返回的.wasm文件。服务器返回头要加 Content-Type 值为 application/wasm , Content-Length和文件内容
@WebFilter(filterName = "wasmFilter", urlPatterns = { "*.wasm"})
public class WASMFilter implements Filter{
	@Override
	public void doFilter(ServletRequest req, ServletResponse resp, FilterChain chain)
			throws IOException, ServletException {
		resp.setContentType("application/wasm");
		HttpServletRequest request=(HttpServletRequest)req;
		String filePath=request.getServletContext().getRealPath("/")+request.getServletPath();
		File file=new File(filePath);
		long len=file.length();
		resp.setContentLengthLong(len);
		FileInputStream input=new FileInputStream(file);
		
		byte[] buf=new byte[1024];
		int readed=0;
		while((readed=input.read(buf))!=-1) {
			resp.getOutputStream().write(buf,0,readed);
		}
		System.out.println(request.getRequestURI()+",len="+len);
		input.close();//FileInputStream实现AutoCloseable接口的自动关闭
	}
}
