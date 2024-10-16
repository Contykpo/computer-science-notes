
2024-10-16 08:59

Status: #In-Production

Tags: #Proxy-Pattern #Design-Pattern #Abstraction #Composition #Lazy-Initialization #Decorator-Pattern #Adapter-Pattern

# Proxy Pattern

**Proxy** is a structural design pattern that lets you provide a substitute or placeholder for another object. A proxy controls access to the original object, allowing you to perform something either before or after the request gets through to the original object.

The #Proxy-Pattern does not add functionality to an object like the #Decorator-Pattern does, but it does proxy an object to another object and control access from one object to another without grouping functionality like a **Decorator** would, or responding to other messages like the #Adapter-Pattern would.
#### Example Problem:

**Why would you want to control access to an object?** Lets suppose you have a massive object that consumes a vast amount of system resources. You need it from time to time, but not always.

You could implement #Lazy-Initialization: create this object only when it’s actually needed. All of the object’s clients would need to execute some deferred initialization code. Unfortunately, this would probably cause a lot of code duplication.

#### Solution:

The #Proxy-Pattern suggests that you create a new proxy class with the same interface as an original service object. Then you update your app so that it passes the proxy object to all of the original object’s clients. Upon receiving a request from a client, the proxy creates a real service object and delegates all the work to it.
But **what’s the benefit?** If you need to execute something either before or after the primary logic of the class, the proxy lets you do this without changing that class. Since the proxy implements the same interface as the original class, it can be passed to any client that expects a real service object.

## Applicability of the Proxy Pattern

- #Lazy-Initialization (virtual proxy). This is when you have a heavyweight service object that wastes system resources by being always up, even though you only need it from time to time.
- **Access control** (protection proxy). This is when you want only specific clients to be able to use the service object.
- **Local execution of a remote service** (remote proxy). This is when the service object is located on a remote server.
- **Logging requests** (logging proxy). This is when you want to keep a history of requests to the service object.
- **Caching request results** (caching proxy). This is when you need to cache results of client requests and manage the life cycle of this cache, especially if results are quite large.
- **Smart reference**. This is when you need to be able to dismiss a heavyweight object once there are no clients that use it.

## Proxy Pattern Structure

**Service Interface**: declares the interface of the Service. The proxy must follow this interface to be able to disguise itself as a service object.

**Service**: a class that provides some useful business logic.

**Proxy**: a class that has a reference field that points to a service object. After the proxy finishes its processing (e.g., lazy initialization, logging, access control, caching, etc.), it passes the request to the service object.
Usually, proxies manage the full lifecycle of their service objects.

**Client**: a class that should work with both services and proxies via the same interface. This way you can pass a proxy into any code that expects a service object.

## Example Code

This example illustrates how the **Proxy** pattern can help to introduce lazy initialization and caching to a 3rd-party YouTube integration library.

The library provides us with the video downloading class. However, it’s very inefficient. If the client application requests the same video multiple times, the library just downloads it over and over, instead of caching and reusing the first downloaded file.

The proxy class implements the same interface as the original downloader and delegates it all the work. However, it keeps track of the downloaded files and returns the cached result when the app requests the same video multiple times.

```
// The interface of a remote service.
interface ThirdPartyYouTubeLib is
    method listVideos()
    method getVideoInfo(id)
    method downloadVideo(id)

// The concrete implementation of a service connector. Methods
// of this class can request information from YouTube. The speed
// of the request depends on a user's internet connection as
// well as YouTube's. The application will slow down if a lot of
// requests are fired at the same time, even if they all request
// the same information.
class ThirdPartyYouTubeClass implements ThirdPartyYouTubeLib is
    method listVideos() is
        // Send an API request to YouTube.

    method getVideoInfo(id) is
        // Get metadata about some video.

    method downloadVideo(id) is
        // Download a video file from YouTube.

// To save some bandwidth, we can cache request results and keep
// them for some time. But it may be impossible to put such code
// directly into the service class. For example, it could have
// been provided as part of a third party library and/or defined
// as `final`. That's why we put the caching code into a new
// proxy class which implements the same interface as the
// service class. It delegates to the service object only when
// the real requests have to be sent.
class CachedYouTubeClass implements ThirdPartyYouTubeLib is
    private field service: ThirdPartyYouTubeLib
    private field listCache, videoCache
    field needReset

    constructor CachedYouTubeClass(service: ThirdPartyYouTubeLib) is
        this.service = service

    method listVideos() is
        if (listCache == null || needReset)
            listCache = service.listVideos()
        return listCache

    method getVideoInfo(id) is
        if (videoCache == null || needReset)
            videoCache = service.getVideoInfo(id)
        return videoCache

    method downloadVideo(id) is
        if (!downloadExists(id) || needReset)
            service.downloadVideo(id)

// The GUI class, which used to work directly with a service
// object, stays unchanged as long as it works with the service
// object through an interface. We can safely pass a proxy
// object instead of a real service object since they both
// implement the same interface.
class YouTubeManager is
    protected field service: ThirdPartyYouTubeLib

    constructor YouTubeManager(service: ThirdPartyYouTubeLib) is
        this.service = service

    method renderVideoPage(id) is
        info = service.getVideoInfo(id)
        // Render the video page.

    method renderListPanel() is
        list = service.listVideos()
        // Render the list of video thumbnails.

    method reactOnUserInput() is
        renderVideoPage()
        renderListPanel()

// The application can configure proxies on the fly.
class Application is
    method init() is
        aYouTubeService = new ThirdPartyYouTubeClass()
        aYouTubeProxy = new CachedYouTubeClass(aYouTubeService)
        manager = new YouTubeManager(aYouTubeProxy)
        manager.reactOnUserInput()
```


# References

- [Further Information on the Proxy Pattern](https://refactoring.guru/design-patterns/proxy).
- [[Decorator Programming Pattern]].
- [[Adapter Programming Pattern]].
